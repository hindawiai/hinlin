<शैली गुरु>
/*
 * dvb_filter.h
 *
 * Copyright (C) 2003 Convergence GmbH
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#अगर_अघोषित _DVB_FILTER_H_
#घोषणा _DVB_FILTER_H_

#समावेश <linux/slab.h>

#समावेश <media/demux.h>

प्रकार पूर्णांक (dvb_filter_pes2ts_cb_t) (व्योम *, अचिन्हित अक्षर *);

काष्ठा dvb_filter_pes2ts अणु
	अचिन्हित अक्षर buf[188];
	अचिन्हित अक्षर cc;
	dvb_filter_pes2ts_cb_t *cb;
	व्योम *priv;
पूर्ण;

व्योम dvb_filter_pes2ts_init(काष्ठा dvb_filter_pes2ts *p2ts, अचिन्हित लघु pid,
			    dvb_filter_pes2ts_cb_t *cb, व्योम *priv);

पूर्णांक dvb_filter_pes2ts(काष्ठा dvb_filter_pes2ts *p2ts, अचिन्हित अक्षर *pes,
		      पूर्णांक len, पूर्णांक payload_start);


#घोषणा PROG_STREAM_MAP  0xBC
#घोषणा PRIVATE_STREAM1  0xBD
#घोषणा PADDING_STREAM   0xBE
#घोषणा PRIVATE_STREAM2  0xBF
#घोषणा AUDIO_STREAM_S   0xC0
#घोषणा AUDIO_STREAM_E   0xDF
#घोषणा VIDEO_STREAM_S   0xE0
#घोषणा VIDEO_STREAM_E   0xEF
#घोषणा ECM_STREAM       0xF0
#घोषणा EMM_STREAM       0xF1
#घोषणा DSM_CC_STREAM    0xF2
#घोषणा ISO13522_STREAM  0xF3
#घोषणा PROG_STREAM_सूची  0xFF

#घोषणा DVB_PICTURE_START    0x00
#घोषणा DVB_USER_START       0xb2
#घोषणा DVB_SEQUENCE_HEADER  0xb3
#घोषणा DVB_SEQUENCE_ERROR   0xb4
#घोषणा DVB_EXTENSION_START  0xb5
#घोषणा DVB_SEQUENCE_END     0xb7
#घोषणा DVB_GOP_START        0xb8
#घोषणा DVB_EXCEPT_SLICE     0xb0

#घोषणा SEQUENCE_EXTENSION           0x01
#घोषणा SEQUENCE_DISPLAY_EXTENSION   0x02
#घोषणा PICTURE_CODING_EXTENSION     0x08
#घोषणा QUANT_MATRIX_EXTENSION       0x03
#घोषणा PICTURE_DISPLAY_EXTENSION    0x07

#घोषणा I_FRAME 0x01
#घोषणा B_FRAME 0x02
#घोषणा P_FRAME 0x03

/* Initialize sequence_data */
#घोषणा INIT_HORIZONTAL_SIZE        720
#घोषणा INIT_VERTICAL_SIZE          576
#घोषणा INIT_ASPECT_RATIO          0x02
#घोषणा INIT_FRAME_RATE            0x03
#घोषणा INIT_DISP_HORIZONTAL_SIZE   540
#घोषणा INIT_DISP_VERTICAL_SIZE     576


//flags2
#घोषणा PTS_DTS_FLAGS    0xC0
#घोषणा ESCR_FLAG        0x20
#घोषणा ES_RATE_FLAG     0x10
#घोषणा DSM_TRICK_FLAG   0x08
#घोषणा ADD_CPY_FLAG     0x04
#घोषणा PES_CRC_FLAG     0x02
#घोषणा PES_EXT_FLAG     0x01

//pts_dts flags
#घोषणा PTS_ONLY         0x80
#घोषणा PTS_DTS          0xC0

#घोषणा TS_SIZE        188
#घोषणा TRANS_ERROR    0x80
#घोषणा PAY_START      0x40
#घोषणा TRANS_PRIO     0x20
#घोषणा PID_MASK_HI    0x1F
//flags
#घोषणा TRANS_SCRMBL1  0x80
#घोषणा TRANS_SCRMBL2  0x40
#घोषणा ADAPT_FIELD    0x20
#घोषणा PAYLOAD        0x10
#घोषणा COUNT_MASK     0x0F

// adaptation flags
#घोषणा DISCON_IND     0x80
#घोषणा RAND_ACC_IND   0x40
#घोषणा ES_PRI_IND     0x20
#घोषणा PCR_FLAG       0x10
#घोषणा OPCR_FLAG      0x08
#घोषणा SPLICE_FLAG    0x04
#घोषणा TRANS_PRIV     0x02
#घोषणा ADAP_EXT_FLAG  0x01

// adaptation extension flags
#घोषणा LTW_FLAG       0x80
#घोषणा PIECE_RATE     0x40
#घोषणा SEAM_SPLICE    0x20


#घोषणा MAX_PLENGTH 0xFFFF
#घोषणा MMAX_PLENGTH (256*MAX_PLENGTH)

#अगर_अघोषित IPACKS
#घोषणा IPACKS 2048
#पूर्ण_अगर

काष्ठा ipack अणु
	पूर्णांक size;
	पूर्णांक found;
	u8 *buf;
	u8 cid;
	u32 plength;
	u8 plen[2];
	u8 flag1;
	u8 flag2;
	u8 hlength;
	u8 pts[5];
	u16 *pid;
	पूर्णांक mpeg;
	u8 check;
	पूर्णांक which;
	पूर्णांक करोne;
	व्योम *data;
	व्योम (*func)(u8 *buf,  पूर्णांक size, व्योम *priv);
	पूर्णांक count;
	पूर्णांक repack_subids;
पूर्ण;

काष्ठा dvb_video_info अणु
	u32 horizontal_size;
	u32 vertical_size;
	u32 aspect_ratio;
	u32 framerate;
	u32 video_क्रमmat;
	u32 bit_rate;
	u32 comp_bit_rate;
	u32 vbv_buffer_size;
	s16 vbv_delay;
	u32 CSPF;
	u32 off;
पूर्ण;

#घोषणा OFF_SIZE 4
#घोषणा FIRST_FIELD 0
#घोषणा SECOND_FIELD 1
#घोषणा VIDEO_FRAME_PICTURE 0x03

काष्ठा mpg_picture अणु
	पूर्णांक       channel;
	काष्ठा dvb_video_info vinfo;
	u32      *sequence_gop_header;
	u32      *picture_header;
	s32       समय_code;
	पूर्णांक       low_delay;
	पूर्णांक       बंदd_gop;
	पूर्णांक       broken_link;
	पूर्णांक       sequence_header_flag;
	पूर्णांक       gop_flag;
	पूर्णांक       sequence_end_flag;

	u8        profile_and_level;
	s32       picture_coding_parameter;
	u32       matrix[32];
	s8        matrix_change_flag;

	u8        picture_header_parameter;
  /* bit 0 - 2: bwd f code
     bit 3    : fpb vector
     bit 4 - 6: fwd f code
     bit 7    : fpf vector */

	पूर्णांक       mpeg1_flag;
	पूर्णांक       progressive_sequence;
	पूर्णांक       sequence_display_extension_flag;
	u32       sequence_header_data;
	s16       last_frame_centre_horizontal_offset;
	s16       last_frame_centre_vertical_offset;

	u32       pts[2]; /* [0] 1st field, [1] 2nd field */
	पूर्णांक       top_field_first;
	पूर्णांक       repeat_first_field;
	पूर्णांक       progressive_frame;
	पूर्णांक       bank;
	पूर्णांक       क्रमward_bank;
	पूर्णांक       backward_bank;
	पूर्णांक       compress;
	s16       frame_centre_horizontal_offset[OFF_SIZE];
		  /* [0-2] 1st field, [3] 2nd field */
	s16       frame_centre_vertical_offset[OFF_SIZE];
		  /* [0-2] 1st field, [3] 2nd field */
	s16       temporal_reference[2];
		  /* [0] 1st field, [1] 2nd field */

	s8        picture_coding_type[2];
		  /* [0] 1st field, [1] 2nd field */
	s8        picture_काष्ठाure[2];
		  /* [0] 1st field, [1] 2nd field */
	s8        picture_display_extension_flag[2];
		  /* [0] 1st field, [1] 2nd field */
		  /* picture_display_extenion() 0:no 1:निकास*/
	s8        pts_flag[2];
		  /* [0] 1st field, [1] 2nd field */
पूर्ण;

काष्ठा dvb_audio_info अणु
	पूर्णांक layer;
	u32 bit_rate;
	u32 frequency;
	u32 mode;
	u32 mode_extension ;
	u32 emphasis;
	u32 framesize;
	u32 off;
पूर्ण;

पूर्णांक dvb_filter_get_ac3info(u8 *mbuf, पूर्णांक count, काष्ठा dvb_audio_info *ai, पूर्णांक pr);


#पूर्ण_अगर
