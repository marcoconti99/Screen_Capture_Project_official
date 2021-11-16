#include "../include/ScreenRecorder.h"

using namespace std;

ScreenRecorder::ScreenRecorder()
{

	avdevice_register_all();
	cout<<"\nall required functions are registered successfully";
}

ScreenRecorder::~ScreenRecorder()
{

	avformat_close_input(&pAVFormatContext);
	if( !pAVFormatContext )
	{
		cout<<"\nfile closed sucessfully";
	}
	else
	{
		cout<<"\nunable to close the file";
		exit(1);
	}

	avformat_free_context(pAVFormatContext);
	if( !pAVFormatContext )
	{
		cout<<"\navformat free successfully";
	}
	else
	{
		cout<<"\nunable to free avformat context";
		exit(1);
	}

}



int ScreenRecorder::openCamera()
{

	value = 0;
	options = NULL;
	AVFormatContext *pAVFormatContext = NULL;

	pAVFormatContext = avformat_alloc_context();//Allocate an AVFormatContext.

	/* current below is for screen recording. to connect with camera use v4l2 as a input parameter for av_find_input_format */ 
	pAVInputFormat = av_find_input_format("x11grab");
  	value = avformat_open_input(&pAVFormatContext, ":1.0+0,0", pAVInputFormat, NULL);  //Open an input stream and read the header. 0 if success
	
	if(value != 0)
	{
	   cout<<"\n error in opening input device";
	   exit(1);
	}

	/* set frame per second */
	value = av_dict_set( &options,"framerate","30",0 );  //Dictionary is like maps-> key =framerate, value = 30, >0 success
	
    if(value < 0)
	{
	  cout<<"\nerror in setting dictionary value";
	   exit(1);
	}

	value = av_dict_set( &options, "preset", "medium", 0 );
	if(value < 0)
	{
	  cout<<"\nerror in setting preset values";
	  exit(1);
	}

//	value = avformat_find_stream_info(pAVFormatContext,NULL);
	if(value < 0)
	{
	  cout<<"\nunable to find the stream information";
	  exit(1);
	}

	VideoStreamIndx = -1;

	/* find the first video stream index . Also there is an API available to do the below operations */

	for(int i = 0; i < pAVFormatContext->nb_streams; i++ ) // find video stream posistion/index.
	{
	  if( pAVFormatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO )
	  {
	     VideoStreamIndx = i;
	     break;
	  }

	} 

	if( VideoStreamIndx == -1)
	{
	  cout<<"\nunable to find the video stream index. (-1)";
	  exit(1);
	}

    //INIZIO MODIFICA

	// assign pAVFormatContext to VideoStreamIndx
	AVCodecParameters *pLocalCodecParam = pAVFormatContext->streams[VideoStreamIndx]->codecpar; 

	pAVCodec = avcodec_find_decoder(pLocalCodecParam->codec_id);
	if( pAVCodec == NULL )
	{
	  cout<<"\nunable to find the decoder";
	  exit(1);
	}

//
   
    pAVCodecContext = avcodec_alloc_context3(pAVCodec);
    avcodec_parameters_to_context(pAVCodecContext, pLocalCodecParam);
//

	value = avcodec_open2(pAVCodecContext, pAVCodec , NULL);//Initialize the AVCodecContext to use the given AVCodec.
	if( value < 0 )
	{
	  cout<<"\nunable to open the av codec";
	  exit(1);
	}
    

    return 0;
}




int ScreenRecorder::init_outputfile()
{
	outAVFormatContext = NULL;
	value = 0;
	output_file = "../media/output.mp4";

	avformat_alloc_output_context2(&outAVFormatContext, NULL, NULL, output_file);
	if (!outAVFormatContext)
	{
		cout<<"\nerror in allocating av format output context";
		exit(1);
	}

/* Returns the output format in the list of registered output formats which best matches the provided parameters, or returns NULL if there is no match. */
	output_format = av_guess_format(NULL, output_file ,NULL);
	if( !output_format )
	{
	 cout<<"\nerror in guessing the video format. try with correct format";
	 exit(1);
	}

	video_st = avformat_new_stream(outAVFormatContext ,NULL);
	if( !video_st )
	{
		cout<<"\nerror in creating a av format new stream";
		exit(1);
	}

	//spostata al posto di COMMENTA
	
	//
    outAVCodec = avcodec_find_encoder(AV_CODEC_ID_MPEG4);
	if (!outAVCodec)
	{
		cout << "\nerror in finding the av codecs. try again with correct codec";
		exit(1);
	}
//
	outAVCodecContext = avcodec_alloc_context3(outAVCodec);

	if( !outAVCodecContext )
	{
	  	cout<<"\nerror in allocating the codec contexts";
		exit(1);
	}

	/* set property of the video file */


	outAVCodecContext->codec_id = AV_CODEC_ID_MPEG4;// AV_CODEC_ID_MPEG4; // AV_CODEC_ID_H264 // AV_CODEC_ID_MPEG1VIDEO
	outAVCodecContext->codec_type = AVMEDIA_TYPE_VIDEO;
	outAVCodecContext->pix_fmt  = AV_PIX_FMT_YUV420P;
	outAVCodecContext->bit_rate = 400000; // 2500000
	outAVCodecContext->width = 1920;
	outAVCodecContext->height = 1080;
	outAVCodecContext->gop_size = 3;
	outAVCodecContext->max_b_frames = 2;
	outAVCodecContext->time_base.num = 1;
	outAVCodecContext->time_base.den = 30; // 15fps

	if (codec_id == AV_CODEC_ID_H264)
	{
	 av_opt_set(outAVCodecContext->priv_data, "preset", "slow", 0);
	}

	     //COMMENTATA
	
	

	/* Some container formats (like MP4) require global headers to be present
	   Mark the encoder so that it behaves accordingly. */

	if ( outAVFormatContext->oformat->flags & AVFMT_GLOBALHEADER)
	{
		outAVCodecContext->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
	}

	value = avcodec_open2(outAVCodecContext, outAVCodec, NULL);
	if( value < 0)
	{
		cout<<"\nerror in opening the avcodec";
		exit(1);
	}

	/* create empty video file */
	if ( !(outAVFormatContext->flags & AVFMT_NOFILE) )
	{
		int ret = avio_open2(&outAVFormatContext->pb , output_file , AVIO_FLAG_WRITE ,NULL, NULL);
	 if(  ret < 0 ) //apre output file in scrittura
	 {
	  cout<<"\nerror in creating the video file";
	  exit(1);
	 }
	}

	if(!outAVFormatContext->nb_streams)
	{
		cout<<"\noutput file dose not contain any stream";
	  	exit(1);
	}
	

	/* imp: mp4 container or some advanced container file required header information*/
	value = avformat_write_header(outAVFormatContext , &options);
	if(value < 0)
	{
		cout<<"\nerror in writing the header context"<<value;
		exit(1);
	}


	// uncomment here to view the complete video file informations
	cout<<"\n\nOutput file information :\n\n";
	av_dump_format(outAVFormatContext , 0 ,output_file ,1);

	


return 0;
}

int ScreenRecorder::CaptureVideoFrames()
{
	int flag;
	int frameFinished;//when you decode a single packet, you still don't have information enough to have a frame [depending on the type of codec, some of them //you do], when you decode a GROUP of packets that represents a frame, then you have a picture! that's why frameFinished will let //you know you decoded enough to have a frame.

	int frame_index = 0;
	value = 0;

	pAVPacket = (AVPacket *)av_malloc(sizeof(AVPacket));
	
	pAVFrame = av_frame_alloc();
	if( !pAVFrame )
	{
	 cout<<"\nunable to release the avframe resources";
	 exit(1);
	}

	outFrame = av_frame_alloc();//Allocate an AVFrame and set its fields to default values.
	if( !outFrame )
	{
	 cout<<"\nunable to release the avframe resources for outframe";
	 exit(1);
	}

	int video_outbuf_size;
	int nbytes = av_image_get_buffer_size(outAVCodecContext->pix_fmt,outAVCodecContext->width,outAVCodecContext->height,32);
	uint8_t *video_outbuf = (uint8_t*)av_malloc(nbytes);
	if( video_outbuf == NULL )
	{
		cout<<"\nunable to allocate memory";
		exit(1);
	}

	// Setup the data pointers and linesizes based on the specified image parameters and the provided array.
	value = av_image_fill_arrays( outFrame->data, outFrame->linesize, video_outbuf , AV_PIX_FMT_YUV420P, outAVCodecContext->width,outAVCodecContext->height,1 ); // returns : the size in bytes required for src
	if(value < 0)
	{
		cout<<"\nerror in filling image array";
	}

	SwsContext* swsCtx_ ;

	// Allocate and return swsContext.
	// a pointer to an allocated context, or NULL in case of error
	// Deprecated : Use sws_getCachedContext() instead.
	swsCtx_ = sws_getCachedContext(swsCtx_,pAVCodecContext->width,
		                pAVCodecContext->height,
		                pAVCodecContext->pix_fmt,
		                outAVCodecContext->width,
				      	outAVCodecContext->height,
		                outAVCodecContext->pix_fmt,
		                SWS_BICUBIC, NULL, NULL, NULL);


int ii = 0;
int no_frames = 100;
cout<<"\nenter No. of frames to capture : ";
cin>>no_frames;

	AVPacket outPacket;
	int j = 0;

	int got_picture;

	while( av_read_frame( pAVFormatContext , pAVPacket ) >= 0 ) //lettura frame da input
	{
	if( ii++ == no_frames )break;
		if(pAVPacket->stream_index == VideoStreamIndx)
		{
			value = avcodec_send_packet( pAVCodecContext ,  pAVPacket );
			if( value < 0)
			{
				cout<<"unable to decode video";
			}
            //pAVFrame , &frameFinished ,
             
			
			if(! avcodec_receive_frame(pAVCodecContext, pAVFrame))// Frame successfully decoded :)
			{
				sws_scale(swsCtx_, pAVFrame->data, pAVFrame->linesize,0, pAVCodecContext->height, outFrame->data,outFrame->linesize);
				
				outPacket.data = NULL;    // packet data will be allocated by the encoder
				outPacket.size = 0;

				//avcodec_encode_video2(outAVCodecContext , &outPacket ,outFrame , &got_picture);
                avcodec_send_frame(outAVCodecContext, outFrame);
                
				
				if(!avcodec_receive_packet(outAVCodecContext, &outPacket))
				{

                    //MODIFICA

					AVStream *in_stream, *out_stream;
					
					in_stream = pAVFormatContext->streams[pAVPacket->stream_index];
					out_stream = outAVFormatContext->streams[pAVPacket->stream_index];

					//MODIFICA

					if(outPacket.pts != AV_NOPTS_VALUE)
						outPacket.pts = av_rescale_q(outPacket.pts,  in_stream->time_base, out_stream->time_base);
					if(outPacket.dts != AV_NOPTS_VALUE)
						outPacket.dts = av_rescale_q(outPacket.dts, in_stream->time_base, out_stream->time_base);
				
					printf("Write frame %3d (size= %2d)\n", j++, outPacket.size/1000);
					if(av_write_frame(outAVFormatContext , &outPacket) != 0)
					{
						cout<<"\nerror in writing video frame";
					}

				av_packet_unref(&outPacket);
				} // got_picture

			av_packet_unref(&outPacket);
			} // frameFinished

		}
	}// End of while-loop

	value = av_write_trailer(outAVFormatContext);
	if( value < 0)
	{
		cout<<"\nerror in writing av trailer";
		exit(1);
	}


//THIS WAS ADDED LATER
av_free(video_outbuf);



return 0;
}

