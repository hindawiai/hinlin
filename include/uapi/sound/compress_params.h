<शैली गुरु>
/* SPDX-License-Identअगरier: ((GPL-2.0 WITH Linux-syscall-note) AND MIT) */
/*
 *  compress_params.h - codec types and parameters क्रम compressed data
 *  streaming पूर्णांकerface
 *
 *  Copyright (C) 2011 Intel Corporation
 *  Authors:	Pierre-Louis Bossart <pierre-louis.bossart@linux.पूर्णांकel.com>
 *              Vinod Koul <vinod.koul@linux.पूर्णांकel.com>
 *
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *  This program is मुक्त software; you can redistribute it and/or modअगरy
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; version 2 of the License.
 *
 *  This program is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  General Public License क्रम more details.
 *
 *  You should have received a copy of the GNU General Public License aदीर्घ
 *  with this program; अगर not, ग_लिखो to the Free Software Foundation, Inc.,
 *  59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * The definitions in this file are derived from the OpenMAX AL version 1.1
 * and OpenMAX IL v 1.1.2 header files which contain the copyright notice below.
 *
 * Copyright (c) 2007-2010 The Khronos Group Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining
 * a copy of this software and/or associated करोcumentation files (the
 * "Materials "), to deal in the Materials without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sublicense, and/or sell copies of the Materials, and to
 * permit persons to whom the Materials are furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Materials.
 *
 * THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * MATERIALS OR THE USE OR OTHER DEALINGS IN THE MATERIALS.
 *
 */
#अगर_अघोषित __SND_COMPRESS_PARAMS_H
#घोषणा __SND_COMPRESS_PARAMS_H

#समावेश <linux/types.h>

/* AUDIO CODECS SUPPORTED */
#घोषणा MAX_NUM_CODECS 32
#घोषणा MAX_NUM_CODEC_DESCRIPTORS 32
#घोषणा MAX_NUM_BITRATES 32
#घोषणा MAX_NUM_SAMPLE_RATES 32

/* Codecs are listed linearly to allow क्रम extensibility */
#घोषणा SND_AUDIOCODEC_PCM                   ((__u32) 0x00000001)
#घोषणा SND_AUDIOCODEC_MP3                   ((__u32) 0x00000002)
#घोषणा SND_AUDIOCODEC_AMR                   ((__u32) 0x00000003)
#घोषणा SND_AUDIOCODEC_AMRWB                 ((__u32) 0x00000004)
#घोषणा SND_AUDIOCODEC_AMRWBPLUS             ((__u32) 0x00000005)
#घोषणा SND_AUDIOCODEC_AAC                   ((__u32) 0x00000006)
#घोषणा SND_AUDIOCODEC_WMA                   ((__u32) 0x00000007)
#घोषणा SND_AUDIOCODEC_REAL                  ((__u32) 0x00000008)
#घोषणा SND_AUDIOCODEC_VORBIS                ((__u32) 0x00000009)
#घोषणा SND_AUDIOCODEC_FLAC                  ((__u32) 0x0000000A)
#घोषणा SND_AUDIOCODEC_IEC61937              ((__u32) 0x0000000B)
#घोषणा SND_AUDIOCODEC_G723_1                ((__u32) 0x0000000C)
#घोषणा SND_AUDIOCODEC_G729                  ((__u32) 0x0000000D)
#घोषणा SND_AUDIOCODEC_BESPOKE               ((__u32) 0x0000000E)
#घोषणा SND_AUDIOCODEC_ALAC                  ((__u32) 0x0000000F)
#घोषणा SND_AUDIOCODEC_APE                   ((__u32) 0x00000010)
#घोषणा SND_AUDIOCODEC_MAX                   SND_AUDIOCODEC_APE

/*
 * Profile and modes are listed with bit masks. This allows क्रम a
 * more compact representation of fields that will not evolve
 * (in contrast to the list of codecs)
 */

#घोषणा SND_AUDIOPROखाता_PCM                 ((__u32) 0x00000001)

/* MP3 modes are only useful क्रम encoders */
#घोषणा SND_AUDIOCHANMODE_MP3_MONO           ((__u32) 0x00000001)
#घोषणा SND_AUDIOCHANMODE_MP3_STEREO         ((__u32) 0x00000002)
#घोषणा SND_AUDIOCHANMODE_MP3_JOINTSTEREO    ((__u32) 0x00000004)
#घोषणा SND_AUDIOCHANMODE_MP3_DUAL           ((__u32) 0x00000008)

#घोषणा SND_AUDIOPROखाता_AMR                 ((__u32) 0x00000001)

/* AMR modes are only useful क्रम encoders */
#घोषणा SND_AUDIOMODE_AMR_DTX_OFF            ((__u32) 0x00000001)
#घोषणा SND_AUDIOMODE_AMR_VAD1               ((__u32) 0x00000002)
#घोषणा SND_AUDIOMODE_AMR_VAD2               ((__u32) 0x00000004)

#घोषणा SND_AUDIOSTREAMFORMAT_UNDEFINED	     ((__u32) 0x00000000)
#घोषणा SND_AUDIOSTREAMFORMAT_CONFORMANCE    ((__u32) 0x00000001)
#घोषणा SND_AUDIOSTREAMFORMAT_IF1            ((__u32) 0x00000002)
#घोषणा SND_AUDIOSTREAMFORMAT_IF2            ((__u32) 0x00000004)
#घोषणा SND_AUDIOSTREAMFORMAT_FSF            ((__u32) 0x00000008)
#घोषणा SND_AUDIOSTREAMFORMAT_RTPPAYLOAD     ((__u32) 0x00000010)
#घोषणा SND_AUDIOSTREAMFORMAT_ITU            ((__u32) 0x00000020)

#घोषणा SND_AUDIOPROखाता_AMRWB               ((__u32) 0x00000001)

/* AMRWB modes are only useful क्रम encoders */
#घोषणा SND_AUDIOMODE_AMRWB_DTX_OFF          ((__u32) 0x00000001)
#घोषणा SND_AUDIOMODE_AMRWB_VAD1             ((__u32) 0x00000002)
#घोषणा SND_AUDIOMODE_AMRWB_VAD2             ((__u32) 0x00000004)

#घोषणा SND_AUDIOPROखाता_AMRWBPLUS           ((__u32) 0x00000001)

#घोषणा SND_AUDIOPROखाता_AAC                 ((__u32) 0x00000001)

/* AAC modes are required क्रम encoders and decoders */
#घोषणा SND_AUDIOMODE_AAC_MAIN               ((__u32) 0x00000001)
#घोषणा SND_AUDIOMODE_AAC_LC                 ((__u32) 0x00000002)
#घोषणा SND_AUDIOMODE_AAC_SSR                ((__u32) 0x00000004)
#घोषणा SND_AUDIOMODE_AAC_LTP                ((__u32) 0x00000008)
#घोषणा SND_AUDIOMODE_AAC_HE                 ((__u32) 0x00000010)
#घोषणा SND_AUDIOMODE_AAC_SCALABLE           ((__u32) 0x00000020)
#घोषणा SND_AUDIOMODE_AAC_ERLC               ((__u32) 0x00000040)
#घोषणा SND_AUDIOMODE_AAC_LD                 ((__u32) 0x00000080)
#घोषणा SND_AUDIOMODE_AAC_HE_PS              ((__u32) 0x00000100)
#घोषणा SND_AUDIOMODE_AAC_HE_MPS             ((__u32) 0x00000200)

/* AAC क्रमmats are required क्रम encoders and decoders */
#घोषणा SND_AUDIOSTREAMFORMAT_MP2ADTS        ((__u32) 0x00000001)
#घोषणा SND_AUDIOSTREAMFORMAT_MP4ADTS        ((__u32) 0x00000002)
#घोषणा SND_AUDIOSTREAMFORMAT_MP4LOAS        ((__u32) 0x00000004)
#घोषणा SND_AUDIOSTREAMFORMAT_MP4LATM        ((__u32) 0x00000008)
#घोषणा SND_AUDIOSTREAMFORMAT_ADIF           ((__u32) 0x00000010)
#घोषणा SND_AUDIOSTREAMFORMAT_MP4FF          ((__u32) 0x00000020)
#घोषणा SND_AUDIOSTREAMFORMAT_RAW            ((__u32) 0x00000040)

#घोषणा SND_AUDIOPROखाता_WMA7                ((__u32) 0x00000001)
#घोषणा SND_AUDIOPROखाता_WMA8                ((__u32) 0x00000002)
#घोषणा SND_AUDIOPROखाता_WMA9                ((__u32) 0x00000004)
#घोषणा SND_AUDIOPROखाता_WMA10               ((__u32) 0x00000008)
#घोषणा SND_AUDIOPROखाता_WMA9_PRO            ((__u32) 0x00000010)
#घोषणा SND_AUDIOPROखाता_WMA9_LOSSLESS       ((__u32) 0x00000020)
#घोषणा SND_AUDIOPROखाता_WMA10_LOSSLESS      ((__u32) 0x00000040)

#घोषणा SND_AUDIOMODE_WMA_LEVEL1             ((__u32) 0x00000001)
#घोषणा SND_AUDIOMODE_WMA_LEVEL2             ((__u32) 0x00000002)
#घोषणा SND_AUDIOMODE_WMA_LEVEL3             ((__u32) 0x00000004)
#घोषणा SND_AUDIOMODE_WMA_LEVEL4             ((__u32) 0x00000008)
#घोषणा SND_AUDIOMODE_WMAPRO_LEVELM0         ((__u32) 0x00000010)
#घोषणा SND_AUDIOMODE_WMAPRO_LEVELM1         ((__u32) 0x00000020)
#घोषणा SND_AUDIOMODE_WMAPRO_LEVELM2         ((__u32) 0x00000040)
#घोषणा SND_AUDIOMODE_WMAPRO_LEVELM3         ((__u32) 0x00000080)

#घोषणा SND_AUDIOSTREAMFORMAT_WMA_ASF        ((__u32) 0x00000001)
/*
 * Some implementations strip the ASF header and only send ASF packets
 * to the DSP
 */
#घोषणा SND_AUDIOSTREAMFORMAT_WMA_NOASF_HDR  ((__u32) 0x00000002)

#घोषणा SND_AUDIOPROखाता_REALAUDIO           ((__u32) 0x00000001)

#घोषणा SND_AUDIOMODE_REALAUDIO_G2           ((__u32) 0x00000001)
#घोषणा SND_AUDIOMODE_REALAUDIO_8            ((__u32) 0x00000002)
#घोषणा SND_AUDIOMODE_REALAUDIO_10           ((__u32) 0x00000004)
#घोषणा SND_AUDIOMODE_REALAUDIO_SURROUND     ((__u32) 0x00000008)

#घोषणा SND_AUDIOPROखाता_VORBIS              ((__u32) 0x00000001)

#घोषणा SND_AUDIOMODE_VORBIS                 ((__u32) 0x00000001)

#घोषणा SND_AUDIOPROखाता_FLAC                ((__u32) 0x00000001)

/*
 * Define quality levels क्रम FLAC encoders, from LEVEL0 (fast)
 * to LEVEL8 (best)
 */
#घोषणा SND_AUDIOMODE_FLAC_LEVEL0            ((__u32) 0x00000001)
#घोषणा SND_AUDIOMODE_FLAC_LEVEL1            ((__u32) 0x00000002)
#घोषणा SND_AUDIOMODE_FLAC_LEVEL2            ((__u32) 0x00000004)
#घोषणा SND_AUDIOMODE_FLAC_LEVEL3            ((__u32) 0x00000008)
#घोषणा SND_AUDIOMODE_FLAC_LEVEL4            ((__u32) 0x00000010)
#घोषणा SND_AUDIOMODE_FLAC_LEVEL5            ((__u32) 0x00000020)
#घोषणा SND_AUDIOMODE_FLAC_LEVEL6            ((__u32) 0x00000040)
#घोषणा SND_AUDIOMODE_FLAC_LEVEL7            ((__u32) 0x00000080)
#घोषणा SND_AUDIOMODE_FLAC_LEVEL8            ((__u32) 0x00000100)

#घोषणा SND_AUDIOSTREAMFORMAT_FLAC           ((__u32) 0x00000001)
#घोषणा SND_AUDIOSTREAMFORMAT_FLAC_OGG       ((__u32) 0x00000002)

/* IEC61937 payloads without CUVP and preambles */
#घोषणा SND_AUDIOPROखाता_IEC61937            ((__u32) 0x00000001)
/* IEC61937 with S/PDIF preambles+CUVP bits in 32-bit containers */
#घोषणा SND_AUDIOPROखाता_IEC61937_SPDIF      ((__u32) 0x00000002)

/*
 * IEC modes are mandatory क्रम decoders. Format स्वतःdetection
 * will only happen on the DSP side with mode 0. The PCM mode should
 * not be used, the PCM codec should be used instead.
 */
#घोषणा SND_AUDIOMODE_IEC_REF_STREAM_HEADER  ((__u32) 0x00000000)
#घोषणा SND_AUDIOMODE_IEC_LPCM		     ((__u32) 0x00000001)
#घोषणा SND_AUDIOMODE_IEC_AC3		     ((__u32) 0x00000002)
#घोषणा SND_AUDIOMODE_IEC_MPEG1		     ((__u32) 0x00000004)
#घोषणा SND_AUDIOMODE_IEC_MP3		     ((__u32) 0x00000008)
#घोषणा SND_AUDIOMODE_IEC_MPEG2		     ((__u32) 0x00000010)
#घोषणा SND_AUDIOMODE_IEC_AACLC		     ((__u32) 0x00000020)
#घोषणा SND_AUDIOMODE_IEC_DTS		     ((__u32) 0x00000040)
#घोषणा SND_AUDIOMODE_IEC_ATRAC		     ((__u32) 0x00000080)
#घोषणा SND_AUDIOMODE_IEC_SACD		     ((__u32) 0x00000100)
#घोषणा SND_AUDIOMODE_IEC_EAC3		     ((__u32) 0x00000200)
#घोषणा SND_AUDIOMODE_IEC_DTS_HD	     ((__u32) 0x00000400)
#घोषणा SND_AUDIOMODE_IEC_MLP		     ((__u32) 0x00000800)
#घोषणा SND_AUDIOMODE_IEC_DST		     ((__u32) 0x00001000)
#घोषणा SND_AUDIOMODE_IEC_WMAPRO	     ((__u32) 0x00002000)
#घोषणा SND_AUDIOMODE_IEC_REF_CXT            ((__u32) 0x00004000)
#घोषणा SND_AUDIOMODE_IEC_HE_AAC	     ((__u32) 0x00008000)
#घोषणा SND_AUDIOMODE_IEC_HE_AAC2	     ((__u32) 0x00010000)
#घोषणा SND_AUDIOMODE_IEC_MPEG_SURROUND	     ((__u32) 0x00020000)

#घोषणा SND_AUDIOPROखाता_G723_1              ((__u32) 0x00000001)

#घोषणा SND_AUDIOMODE_G723_1_ANNEX_A         ((__u32) 0x00000001)
#घोषणा SND_AUDIOMODE_G723_1_ANNEX_B         ((__u32) 0x00000002)
#घोषणा SND_AUDIOMODE_G723_1_ANNEX_C         ((__u32) 0x00000004)

#घोषणा SND_AUDIOPROखाता_G729                ((__u32) 0x00000001)

#घोषणा SND_AUDIOMODE_G729_ANNEX_A           ((__u32) 0x00000001)
#घोषणा SND_AUDIOMODE_G729_ANNEX_B           ((__u32) 0x00000002)

/* <FIXME: multichannel encoders aren't supported क्रम now. Would need
   an additional definition of channel arrangement> */

/* VBR/CBR definitions */
#घोषणा SND_RATECONTROLMODE_CONSTANTBITRATE  ((__u32) 0x00000001)
#घोषणा SND_RATECONTROLMODE_VARIABLEBITRATE  ((__u32) 0x00000002)

/* Encoder options */

काष्ठा snd_enc_wma अणु
	__u32 super_block_align; /* WMA Type-specअगरic data */
पूर्ण;


/**
 * काष्ठा snd_enc_vorbis
 * @quality: Sets encoding quality to n, between -1 (low) and 10 (high).
 * In the शेष mode of operation, the quality level is 3.
 * Normal quality range is 0 - 10.
 * @managed: Boolean. Set  bitrate  management  mode. This turns off the
 * normal VBR encoding, but allows hard or soft bitrate स्थिरraपूर्णांकs to be
 * enक्रमced by the encoder. This mode can be slower, and may also be
 * lower quality. It is primarily useful क्रम streaming.
 * @max_bit_rate: Enabled only अगर managed is TRUE
 * @min_bit_rate: Enabled only अगर managed is TRUE
 * @करोwnmix: Boolean. Downmix input from stereo to mono (has no effect on
 * non-stereo streams). Useful क्रम lower-bitrate encoding.
 *
 * These options were extracted from the OpenMAX IL spec and Gstreamer vorbisenc
 * properties
 *
 * For best quality users should specअगरy VBR mode and set quality levels.
 */

काष्ठा snd_enc_vorbis अणु
	__s32 quality;
	__u32 managed;
	__u32 max_bit_rate;
	__u32 min_bit_rate;
	__u32 करोwnmix;
पूर्ण __attribute__((packed, aligned(4)));


/**
 * काष्ठा snd_enc_real
 * @quant_bits: number of coupling quantization bits in the stream
 * @start_region: coupling start region in the stream
 * @num_regions: number of regions value
 *
 * These options were extracted from the OpenMAX IL spec
 */

काष्ठा snd_enc_real अणु
	__u32 quant_bits;
	__u32 start_region;
	__u32 num_regions;
पूर्ण __attribute__((packed, aligned(4)));

/**
 * काष्ठा snd_enc_flac
 * @num: serial number, valid only क्रम OGG क्रमmats
 *	needs to be set by application
 * @gain: Add replay gain tags
 *
 * These options were extracted from the FLAC online करोcumentation
 * at http://flac.sourceक्रमge.net/करोcumentation_tools_flac.hपंचांगl
 *
 * To make the API simpler, it is assumed that the user will select quality
 * profiles. Additional options that affect encoding quality and speed can
 * be added at a later stage अगर needed.
 *
 * By शेष the Subset क्रमmat is used by encoders.
 *
 * TAGS such as pictures, etc, cannot be handled by an offloaded encoder and are
 * not supported in this API.
 */

काष्ठा snd_enc_flac अणु
	__u32 num;
	__u32 gain;
पूर्ण __attribute__((packed, aligned(4)));

काष्ठा snd_enc_generic अणु
	__u32 bw;	/* encoder bandwidth */
	__s32 reserved[15];	/* Can be used क्रम SND_AUDIOCODEC_BESPOKE */
पूर्ण __attribute__((packed, aligned(4)));

काष्ठा snd_dec_flac अणु
	__u16 sample_size;
	__u16 min_blk_size;
	__u16 max_blk_size;
	__u16 min_frame_size;
	__u16 max_frame_size;
	__u16 reserved;
पूर्ण __attribute__((packed, aligned(4)));

काष्ठा snd_dec_wma अणु
	__u32 encoder_option;
	__u32 adv_encoder_option;
	__u32 adv_encoder_option2;
	__u32 reserved;
पूर्ण __attribute__((packed, aligned(4)));

काष्ठा snd_dec_alac अणु
	__u32 frame_length;
	__u8 compatible_version;
	__u8 pb;
	__u8 mb;
	__u8 kb;
	__u32 max_run;
	__u32 max_frame_bytes;
पूर्ण __attribute__((packed, aligned(4)));

काष्ठा snd_dec_ape अणु
	__u16 compatible_version;
	__u16 compression_level;
	__u32 क्रमmat_flags;
	__u32 blocks_per_frame;
	__u32 final_frame_blocks;
	__u32 total_frames;
	__u32 seek_table_present;
पूर्ण __attribute__((packed, aligned(4)));

जोड़ snd_codec_options अणु
	काष्ठा snd_enc_wma wma;
	काष्ठा snd_enc_vorbis vorbis;
	काष्ठा snd_enc_real real;
	काष्ठा snd_enc_flac flac;
	काष्ठा snd_enc_generic generic;
	काष्ठा snd_dec_flac flac_d;
	काष्ठा snd_dec_wma wma_d;
	काष्ठा snd_dec_alac alac_d;
	काष्ठा snd_dec_ape ape_d;
पूर्ण __attribute__((packed, aligned(4)));

/** काष्ठा snd_codec_desc - description of codec capabilities
 * @max_ch: Maximum number of audio channels
 * @sample_rates: Sampling rates in Hz, use values like 48000 क्रम this
 * @num_sample_rates: Number of valid values in sample_rates array
 * @bit_rate: Indexed array containing supported bit rates
 * @num_bitrates: Number of valid values in bit_rate array
 * @rate_control: value is specअगरied by SND_RATECONTROLMODE defines.
 * @profiles: Supported profiles. See SND_AUDIOPROखाता defines.
 * @modes: Supported modes. See SND_AUDIOMODE defines
 * @क्रमmats: Supported क्रमmats. See SND_AUDIOSTREAMFORMAT defines
 * @min_buffer: Minimum buffer size handled by codec implementation
 * @reserved: reserved क्रम future use
 *
 * This काष्ठाure provides a scalar value क्रम profiles, modes and stream
 * क्रमmat fields.
 * If an implementation supports multiple combinations, they will be listed as
 * codecs with dअगरferent descriptors, क्रम example there would be 2 descriptors
 * क्रम AAC-RAW and AAC-ADTS.
 * This entails some redundancy but makes it easier to aव्योम invalid
 * configurations.
 *
 */

काष्ठा snd_codec_desc अणु
	__u32 max_ch;
	__u32 sample_rates[MAX_NUM_SAMPLE_RATES];
	__u32 num_sample_rates;
	__u32 bit_rate[MAX_NUM_BITRATES];
	__u32 num_bitrates;
	__u32 rate_control;
	__u32 profiles;
	__u32 modes;
	__u32 क्रमmats;
	__u32 min_buffer;
	__u32 reserved[15];
पूर्ण __attribute__((packed, aligned(4)));

/** काष्ठा snd_codec
 * @id: Identअगरies the supported audio encoder/decoder.
 *		See SND_AUDIOCODEC macros.
 * @ch_in: Number of input audio channels
 * @ch_out: Number of output channels. In हाल of contradiction between
 *		this field and the channelMode field, the channelMode field
 *		overrides.
 * @sample_rate: Audio sample rate of input data in Hz, use values like 48000
 *		क्रम this.
 * @bit_rate: Bitrate of encoded data. May be ignored by decoders
 * @rate_control: Encoding rate control. See SND_RATECONTROLMODE defines.
 *               Encoders may rely on profiles क्रम quality levels.
 *		 May be ignored by decoders.
 * @profile: Mandatory क्रम encoders, can be mandatory क्रम specअगरic
 *		decoders as well. See SND_AUDIOPROखाता defines.
 * @level: Supported level (Only used by WMA at the moment)
 * @ch_mode: Channel mode क्रम encoder. See SND_AUDIOCHANMODE defines
 * @क्रमmat: Format of encoded bistream. Mandatory when defined.
 *		See SND_AUDIOSTREAMFORMAT defines.
 * @align: Block alignment in bytes of an audio sample.
 *		Only required क्रम PCM or IEC क्रमmats.
 * @options: encoder-specअगरic settings
 * @reserved: reserved क्रम future use
 */

काष्ठा snd_codec अणु
	__u32 id;
	__u32 ch_in;
	__u32 ch_out;
	__u32 sample_rate;
	__u32 bit_rate;
	__u32 rate_control;
	__u32 profile;
	__u32 level;
	__u32 ch_mode;
	__u32 क्रमmat;
	__u32 align;
	जोड़ snd_codec_options options;
	__u32 reserved[3];
पूर्ण __attribute__((packed, aligned(4)));

#पूर्ण_अगर
