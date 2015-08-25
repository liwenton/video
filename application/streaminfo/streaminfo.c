#include <stdio.h>

#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavutil/rational.h"
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
   int i, videoindex=-1;
   AVCodecContext  *pCodecCtx;
   AVCodec         *pCodec;
   AVStream	 *pStream;
   AVFrame	 *pFrame; 
   AVPacket	 *packet;
   StreamInfo	 sinfo; 
   FILE *videofp=NULL;
   
   av_register_all();
   avformat_network_init();

   pFormatCtx = avformat_alloc_context();

	int ret;
	ret = avformat_open_input(&pFormatCtx, argv[1], NULL , NULL);
   	if(ret < 0)
	{
		printf("Could not open input stream\n");
        return -1;
   	}

  	ret = avformat_find_stream_info(pFormatCtx, NULL);
   	if(ret < 0)
   	{
		printf("Could not find stream information\n");
   	}

   	for(i=0; i<pFormatCtx->nb_streams; i++)
   	{
		if(pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			videoindex=i;
			break;
		}
	}
	if(i == pFormatCtx->nb_streams)
	{
		printf("nout find a video stream\n");
		return -1;
	}

   	pStream = pFormatCtx->streams[videoindex];
   	pCodecCtx = pFormatCtx->streams[videoindex]->codec;
   	pCodec = avcodec_find_decoder(pCodecCtx->codec_id);

   	if(pCodec == NULL)
   	{
		printf("codec not found\n");
        return -1;
   	}
      
   
   	int64_t dura = pFormatCtx->duration + 5000;
	sinfo.time.duration = dura;
   	sinfo.time.secs = dura / AV_TIME_BASE;
   	sinfo.time.hours = sinfo.time.secs / 3600;
   	sinfo.time.mins = sinfo.time.secs / 60;
   	sinfo.time.secs = sinfo.time.secs % 60;

   	sinfo.bitrate = pCodecCtx->bit_rate / 1000;
   	sinfo.width = pCodecCtx->width;
   	sinfo.height = pCodecCtx->height;

	printf("CodecName  =   %s\n",pCodec->long_name);
   	printf("Duration   =   %02d:%02d:%02d\n", sinfo.time.hours, sinfo.time.mins, sinfo.time.secs);
   	printf("BitRate    =   %d kbps\n",sinfo.bitrate); 
   	printf("Width      =   %d\n",sinfo.width);	
   	printf("Height     =   %d\n",sinfo.height);	
   	printf("GopSize    =   %d\n",pCodecCtx->gop_size);

   	avcodec_close(pCodecCtx);  
   	avformat_close_input(&pFormatCtx);
}
