#include <stdio.h>
#include <string.h>

#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavutil/rational.h"
#include "libavutil/mem.h"
typedef struct
{
   int64_t duration;
   int hours;
   int mins;
   int secs;
}StreamTime;

typedef struct
{
   int width;
   int height;
   int bitrate;
   StreamTime time;
}StreamInfo;


int main(int argc, char *argv[])
{
   	AVFormatContext *pFormatCtx;
   	int 		i, videoindex=-1;
   	AVCodecContext  *pCodecCtx;
   	AVCodec         *pCodec;
   	AVStream	 *pStream;
   	AVFrame	 *pFrame; 
   	AVPacket	 *packet;
   	StreamInfo	 sinfo; 
   	int flags;
   	FILE *videofp=NULL;
   
   	av_register_all();
   	avformat_network_init();
	printf("%s\n", argv[1]);
   	pFormatCtx = avformat_alloc_context();

	if(avformat_open_input(&pFormatCtx, argv[1], NULL, NULL)!=0)
	{
		printf("Could not open input stream\n");
        return -1;
   	}

   	if(avformat_find_stream_info(pFormatCtx, NULL)!=0)
   	{
		printf("Could not find stream information\n");
  	 }

   	for(i=0; i<pFormatCtx->nb_streams; i++)
   	{
		if(pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			videoindex=i;
		}
   	}

   pStream = pFormatCtx->streams[videoindex];
   pCodecCtx = pFormatCtx->streams[videoindex]->codec;
   pCodec = avcodec_find_decoder(pCodecCtx->codec_id);

   if(pCodec == NULL)
   {
	printf("codec not found\n");
        return -1;
   }
      
   if(avcodec_open2(pCodecCtx, pCodec, NULL) < 0)
   {
	printf("can not open codec!\n");
   }

   pFrame = av_frame_alloc();
   packet =(AVPacket *)av_malloc(sizeof(AVPacket));

   for(i=0; i<50; i++)
   {
 	  if(av_read_frame(pFormatCtx, packet)>=0)
  	 {
		int ret = avcodec_decode_video2(pCodecCtx, pFrame, &flags, packet);
		if(ret < 0)
  		 {
    		printf("Decode Error\n");
        	return -1;	
  		 }	
	printf("dts:%lld\n",packet->dts);
   	printf("pts:%lld\n",packet->pts);
   	printf("--------------------------------------\n");
  	 }
   }
   
}
