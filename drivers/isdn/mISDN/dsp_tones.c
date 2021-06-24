<शैली गुरु>
/*
 * Audio support data क्रम ISDN4Linux.
 *
 * Copyright Andreas Eversberg (jolly@eversberg.eu)
 *
 * This software may be used and distributed according to the terms
 * of the GNU General Public License, incorporated herein by reference.
 *
 */

#समावेश <linux/gfp.h>
#समावेश <linux/mISDNअगर.h>
#समावेश <linux/mISDNdsp.h>
#समावेश "core.h"
#समावेश "dsp.h"


#घोषणा DATA_S sample_silence
#घोषणा SIZE_S (&माप_silence)
#घोषणा DATA_GA sample_german_all
#घोषणा SIZE_GA (&माप_german_all)
#घोषणा DATA_GO sample_german_old
#घोषणा SIZE_GO (&माप_german_old)
#घोषणा DATA_DT sample_american_dialtone
#घोषणा SIZE_DT (&माप_american_dialtone)
#घोषणा DATA_RI sample_american_ringing
#घोषणा SIZE_RI (&माप_american_ringing)
#घोषणा DATA_BU sample_american_busy
#घोषणा SIZE_BU (&माप_american_busy)
#घोषणा DATA_S1 sample_special1
#घोषणा SIZE_S1 (&माप_special1)
#घोषणा DATA_S2 sample_special2
#घोषणा SIZE_S2 (&माप_special2)
#घोषणा DATA_S3 sample_special3
#घोषणा SIZE_S3 (&माप_special3)

/***************/
/* tones loops */
/***************/

/* all tones are alaw encoded */
/* the last sample+1 is in phase with the first sample. the error is low */

अटल u8 sample_german_all[] = अणु
	0x80, 0xab, 0x81, 0x6d, 0xfd, 0xdd, 0x5d, 0x9d,
	0x4d, 0xd1, 0x89, 0x88, 0xd0, 0x4c, 0x9c, 0x5c,
	0xdc, 0xfc, 0x6c,
	0x80, 0xab, 0x81, 0x6d, 0xfd, 0xdd, 0x5d, 0x9d,
	0x4d, 0xd1, 0x89, 0x88, 0xd0, 0x4c, 0x9c, 0x5c,
	0xdc, 0xfc, 0x6c,
	0x80, 0xab, 0x81, 0x6d, 0xfd, 0xdd, 0x5d, 0x9d,
	0x4d, 0xd1, 0x89, 0x88, 0xd0, 0x4c, 0x9c, 0x5c,
	0xdc, 0xfc, 0x6c,
	0x80, 0xab, 0x81, 0x6d, 0xfd, 0xdd, 0x5d, 0x9d,
	0x4d, 0xd1, 0x89, 0x88, 0xd0, 0x4c, 0x9c, 0x5c,
	0xdc, 0xfc, 0x6c,
पूर्ण;
अटल u32 माप_german_all = माप(sample_german_all);

अटल u8 sample_german_old[] = अणु
	0xec, 0x68, 0xe1, 0x6d, 0x6d, 0x91, 0x51, 0xed,
	0x6d, 0x01, 0x1e, 0x10, 0x0c, 0x90, 0x60, 0x70,
	0x8c,
	0xec, 0x68, 0xe1, 0x6d, 0x6d, 0x91, 0x51, 0xed,
	0x6d, 0x01, 0x1e, 0x10, 0x0c, 0x90, 0x60, 0x70,
	0x8c,
	0xec, 0x68, 0xe1, 0x6d, 0x6d, 0x91, 0x51, 0xed,
	0x6d, 0x01, 0x1e, 0x10, 0x0c, 0x90, 0x60, 0x70,
	0x8c,
	0xec, 0x68, 0xe1, 0x6d, 0x6d, 0x91, 0x51, 0xed,
	0x6d, 0x01, 0x1e, 0x10, 0x0c, 0x90, 0x60, 0x70,
	0x8c,
पूर्ण;
अटल u32 माप_german_old = माप(sample_german_old);

अटल u8 sample_american_dialtone[] = अणु
	0x2a, 0x18, 0x90, 0x6c, 0x4c, 0xbc, 0x4c, 0x6c,
	0x10, 0x58, 0x32, 0xb9, 0x31, 0x2d, 0x8d, 0x0d,
	0x8d, 0x2d, 0x31, 0x99, 0x0f, 0x28, 0x60, 0xf0,
	0xd0, 0x50, 0xd0, 0x30, 0x60, 0x08, 0x8e, 0x67,
	0x09, 0x19, 0x21, 0xe1, 0xd9, 0xb9, 0x29, 0x67,
	0x83, 0x02, 0xce, 0xbe, 0xee, 0x1a, 0x1b, 0xef,
	0xbf, 0xcf, 0x03, 0x82, 0x66, 0x28, 0xb8, 0xd8,
	0xe0, 0x20, 0x18, 0x08, 0x66, 0x8f, 0x09, 0x61,
	0x31, 0xd1, 0x51, 0xd1, 0xf1, 0x61, 0x29, 0x0e,
	0x98, 0x30, 0x2c, 0x8c, 0x0c, 0x8c, 0x2c, 0x30,
	0xb8, 0x33, 0x59, 0x11, 0x6d, 0x4d, 0xbd, 0x4d,
	0x6d, 0x91, 0x19,
पूर्ण;
अटल u32 माप_american_dialtone = माप(sample_american_dialtone);

अटल u8 sample_american_ringing[] = अणु
	0x2a, 0xe0, 0xac, 0x0c, 0xbc, 0x4c, 0x8c, 0x90,
	0x48, 0xc7, 0xc1, 0xed, 0xcd, 0x4d, 0xcd, 0xed,
	0xc1, 0xb7, 0x08, 0x30, 0xec, 0xcc, 0xcc, 0x8c,
	0x10, 0x58, 0x1a, 0x99, 0x71, 0xed, 0x8d, 0x8d,
	0x2d, 0x41, 0x89, 0x9e, 0x20, 0x70, 0x2c, 0xec,
	0x2c, 0x70, 0x20, 0x86, 0x77, 0xe1, 0x31, 0x11,
	0xd1, 0xf1, 0x81, 0x09, 0xa3, 0x56, 0x58, 0x00,
	0x40, 0xc0, 0x60, 0x38, 0x46, 0x43, 0x57, 0x39,
	0xd9, 0x59, 0x99, 0xc9, 0x77, 0x2f, 0x2e, 0xc6,
	0xd6, 0x28, 0xd6, 0x36, 0x26, 0x2e, 0x8a, 0xa3,
	0x43, 0x63, 0x4b, 0x4a, 0x62, 0x42, 0xa2, 0x8b,
	0x2f, 0x27, 0x37, 0xd7, 0x29, 0xd7, 0xc7, 0x2f,
	0x2e, 0x76, 0xc8, 0x98, 0x58, 0xd8, 0x38, 0x56,
	0x42, 0x47, 0x39, 0x61, 0xc1, 0x41, 0x01, 0x59,
	0x57, 0xa2, 0x08, 0x80, 0xf0, 0xd0, 0x10, 0x30,
	0xe0, 0x76, 0x87, 0x21, 0x71, 0x2d, 0xed, 0x2d,
	0x71, 0x21, 0x9f, 0x88, 0x40, 0x2c, 0x8c, 0x8c,
	0xec, 0x70, 0x98, 0x1b, 0x59, 0x11, 0x8d, 0xcd,
	0xcd, 0xed, 0x31, 0x09, 0xb6, 0xc0, 0xec, 0xcc,
	0x4c, 0xcc, 0xec, 0xc0, 0xc6, 0x49, 0x91, 0x8d,
	0x4d, 0xbd, 0x0d, 0xad, 0xe1,
पूर्ण;
अटल u32 माप_american_ringing = माप(sample_american_ringing);

अटल u8 sample_american_busy[] = अणु
	0x2a, 0x00, 0x6c, 0x4c, 0x4c, 0x6c, 0xb0, 0x66,
	0x99, 0x11, 0x6d, 0x8d, 0x2d, 0x41, 0xd7, 0x96,
	0x60, 0xf0, 0x70, 0x40, 0x58, 0xf6, 0x53, 0x57,
	0x09, 0x89, 0xd7, 0x5f, 0xe3, 0x2a, 0xe3, 0x5f,
	0xd7, 0x89, 0x09, 0x57, 0x53, 0xf6, 0x58, 0x40,
	0x70, 0xf0, 0x60, 0x96, 0xd7, 0x41, 0x2d, 0x8d,
	0x6d, 0x11, 0x99, 0x66, 0xb0, 0x6c, 0x4c, 0x4c,
	0x6c, 0x00, 0x2a, 0x01, 0x6d, 0x4d, 0x4d, 0x6d,
	0xb1, 0x67, 0x98, 0x10, 0x6c, 0x8c, 0x2c, 0x40,
	0xd6, 0x97, 0x61, 0xf1, 0x71, 0x41, 0x59, 0xf7,
	0x52, 0x56, 0x08, 0x88, 0xd6, 0x5e, 0xe2, 0x2a,
	0xe2, 0x5e, 0xd6, 0x88, 0x08, 0x56, 0x52, 0xf7,
	0x59, 0x41, 0x71, 0xf1, 0x61, 0x97, 0xd6, 0x40,
	0x2c, 0x8c, 0x6c, 0x10, 0x98, 0x67, 0xb1, 0x6d,
	0x4d, 0x4d, 0x6d, 0x01,
पूर्ण;
अटल u32 माप_american_busy = माप(sample_american_busy);

अटल u8 sample_special1[] = अणु
	0x2a, 0x2c, 0xbc, 0x6c, 0xd6, 0x71, 0xbd, 0x0d,
	0xd9, 0x80, 0xcc, 0x4c, 0x40, 0x39, 0x0d, 0xbd,
	0x11, 0x86, 0xec, 0xbc, 0xec, 0x0e, 0x51, 0xbd,
	0x8d, 0x89, 0x30, 0x4c, 0xcc, 0xe0, 0xe1, 0xcd,
	0x4d, 0x31, 0x88, 0x8c, 0xbc, 0x50, 0x0f, 0xed,
	0xbd, 0xed, 0x87, 0x10, 0xbc, 0x0c, 0x38, 0x41,
	0x4d, 0xcd, 0x81, 0xd8, 0x0c, 0xbc, 0x70, 0xd7,
	0x6d, 0xbd, 0x2d,
पूर्ण;
अटल u32 माप_special1 = माप(sample_special1);

अटल u8 sample_special2[] = अणु
	0x2a, 0xcc, 0x8c, 0xd7, 0x4d, 0x2d, 0x18, 0xbc,
	0x10, 0xc1, 0xbd, 0xc1, 0x10, 0xbc, 0x18, 0x2d,
	0x4d, 0xd7, 0x8c, 0xcc, 0x2a, 0xcd, 0x8d, 0xd6,
	0x4c, 0x2c, 0x19, 0xbd, 0x11, 0xc0, 0xbc, 0xc0,
	0x11, 0xbd, 0x19, 0x2c, 0x4c, 0xd6, 0x8d, 0xcd,
	0x2a, 0xcc, 0x8c, 0xd7, 0x4d, 0x2d, 0x18, 0xbc,
	0x10, 0xc1, 0xbd, 0xc1, 0x10, 0xbc, 0x18, 0x2d,
	0x4d, 0xd7, 0x8c, 0xcc, 0x2a, 0xcd, 0x8d, 0xd6,
	0x4c, 0x2c, 0x19, 0xbd, 0x11, 0xc0, 0xbc, 0xc0,
	0x11, 0xbd, 0x19, 0x2c, 0x4c, 0xd6, 0x8d, 0xcd,
पूर्ण;
अटल u32 माप_special2 = माप(sample_special2);

अटल u8 sample_special3[] = अणु
	0x2a, 0xbc, 0x18, 0xcd, 0x11, 0x2c, 0x8c, 0xc1,
	0x4d, 0xd6, 0xbc, 0xd6, 0x4d, 0xc1, 0x8c, 0x2c,
	0x11, 0xcd, 0x18, 0xbc, 0x2a, 0xbd, 0x19, 0xcc,
	0x10, 0x2d, 0x8d, 0xc0, 0x4c, 0xd7, 0xbd, 0xd7,
	0x4c, 0xc0, 0x8d, 0x2d, 0x10, 0xcc, 0x19, 0xbd,
	0x2a, 0xbc, 0x18, 0xcd, 0x11, 0x2c, 0x8c, 0xc1,
	0x4d, 0xd6, 0xbc, 0xd6, 0x4d, 0xc1, 0x8c, 0x2c,
	0x11, 0xcd, 0x18, 0xbc, 0x2a, 0xbd, 0x19, 0xcc,
	0x10, 0x2d, 0x8d, 0xc0, 0x4c, 0xd7, 0xbd, 0xd7,
	0x4c, 0xc0, 0x8d, 0x2d, 0x10, 0xcc, 0x19, 0xbd,
पूर्ण;
अटल u32 माप_special3 = माप(sample_special3);

अटल u8 sample_silence[] = अणु
	0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a,
	0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a,
	0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a,
	0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a,
	0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a,
	0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a,
	0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a,
	0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a,
	0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a,
	0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a,
	0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a,
	0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a,
पूर्ण;
अटल u32 माप_silence = माप(sample_silence);

काष्ठा tones_samples अणु
	u32 *len;
	u8 *data;
पूर्ण;
अटल काष्ठा
tones_samples samples[] = अणु
	अणु&माप_german_all, sample_german_allपूर्ण,
	अणु&माप_german_old, sample_german_oldपूर्ण,
	अणु&माप_american_dialtone, sample_american_dialtoneपूर्ण,
	अणु&माप_american_ringing, sample_american_ringingपूर्ण,
	अणु&माप_american_busy, sample_american_busyपूर्ण,
	अणु&माप_special1, sample_special1पूर्ण,
	अणु&माप_special2, sample_special2पूर्ण,
	अणु&माप_special3, sample_special3पूर्ण,
	अणुशून्य, शून्यपूर्ण,
पूर्ण;

/***********************************
 * generate ulaw from alaw samples *
 ***********************************/

व्योम
dsp_audio_generate_ulaw_samples(व्योम)
अणु
	पूर्णांक i, j;

	i = 0;
	जबतक (samples[i].len) अणु
		j = 0;
		जबतक (j < (*samples[i].len)) अणु
			samples[i].data[j] =
				dsp_audio_alaw_to_ulaw[samples[i].data[j]];
			j++;
		पूर्ण
		i++;
	पूर्ण
पूर्ण


/****************************
 * tone sequence definition *
 ****************************/

अटल काष्ठा pattern अणु
	पूर्णांक tone;
	u8 *data[10];
	u32 *siz[10];
	u32 seq[10];
पूर्ण pattern[] = अणु
	अणुTONE_GERMAN_DIALTONE,
	 अणुDATA_GA, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्यपूर्ण,
	 अणुSIZE_GA, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्यपूर्ण,
	 अणु1900, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण पूर्ण,

	अणुTONE_GERMAN_OLDDIALTONE,
	 अणुDATA_GO, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्यपूर्ण,
	 अणुSIZE_GO, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्यपूर्ण,
	 अणु1998, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण पूर्ण,

	अणुTONE_AMERICAN_DIALTONE,
	 अणुDATA_DT, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्यपूर्ण,
	 अणुSIZE_DT, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्यपूर्ण,
	 अणु8000, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण पूर्ण,

	अणुTONE_GERMAN_DIALPBX,
	 अणुDATA_GA, DATA_S, DATA_GA, DATA_S, DATA_GA, DATA_S, शून्य, शून्य, शून्य,
	  शून्यपूर्ण,
	 अणुSIZE_GA, SIZE_S, SIZE_GA, SIZE_S, SIZE_GA, SIZE_S, शून्य, शून्य, शून्य,
	  शून्यपूर्ण,
	 अणु2000, 2000, 2000, 2000, 2000, 12000, 0, 0, 0, 0पूर्ण पूर्ण,

	अणुTONE_GERMAN_OLDDIALPBX,
	 अणुDATA_GO, DATA_S, DATA_GO, DATA_S, DATA_GO, DATA_S, शून्य, शून्य, शून्य,
	  शून्यपूर्ण,
	 अणुSIZE_GO, SIZE_S, SIZE_GO, SIZE_S, SIZE_GO, SIZE_S, शून्य, शून्य, शून्य,
	  शून्यपूर्ण,
	 अणु2000, 2000, 2000, 2000, 2000, 12000, 0, 0, 0, 0पूर्ण पूर्ण,

	अणुTONE_AMERICAN_DIALPBX,
	 अणुDATA_DT, DATA_S, DATA_DT, DATA_S, DATA_DT, DATA_S, शून्य, शून्य, शून्य,
	  शून्यपूर्ण,
	 अणुSIZE_DT, SIZE_S, SIZE_DT, SIZE_S, SIZE_DT, SIZE_S, शून्य, शून्य, शून्य,
	  शून्यपूर्ण,
	 अणु2000, 2000, 2000, 2000, 2000, 12000, 0, 0, 0, 0पूर्ण पूर्ण,

	अणुTONE_GERMAN_RINGING,
	 अणुDATA_GA, DATA_S, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्यपूर्ण,
	 अणुSIZE_GA, SIZE_S, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्यपूर्ण,
	 अणु8000, 32000, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण पूर्ण,

	अणुTONE_GERMAN_OLDRINGING,
	 अणुDATA_GO, DATA_S, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्यपूर्ण,
	 अणुSIZE_GO, SIZE_S, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्यपूर्ण,
	 अणु8000, 40000, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण पूर्ण,

	अणुTONE_AMERICAN_RINGING,
	 अणुDATA_RI, DATA_S, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्यपूर्ण,
	 अणुSIZE_RI, SIZE_S, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्यपूर्ण,
	 अणु8000, 32000, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण पूर्ण,

	अणुTONE_GERMAN_RINGPBX,
	 अणुDATA_GA, DATA_S, DATA_GA, DATA_S, शून्य, शून्य, शून्य, शून्य, शून्य, शून्यपूर्ण,
	 अणुSIZE_GA, SIZE_S, SIZE_GA, SIZE_S, शून्य, शून्य, शून्य, शून्य, शून्य, शून्यपूर्ण,
	 अणु4000, 4000, 4000, 28000, 0, 0, 0, 0, 0, 0पूर्ण पूर्ण,

	अणुTONE_GERMAN_OLDRINGPBX,
	 अणुDATA_GO, DATA_S, DATA_GO, DATA_S, शून्य, शून्य, शून्य, शून्य, शून्य, शून्यपूर्ण,
	 अणुSIZE_GO, SIZE_S, SIZE_GO, SIZE_S, शून्य, शून्य, शून्य, शून्य, शून्य, शून्यपूर्ण,
	 अणु4000, 4000, 4000, 28000, 0, 0, 0, 0, 0, 0पूर्ण पूर्ण,

	अणुTONE_AMERICAN_RINGPBX,
	 अणुDATA_RI, DATA_S, DATA_RI, DATA_S, शून्य, शून्य, शून्य, शून्य, शून्य, शून्यपूर्ण,
	 अणुSIZE_RI, SIZE_S, SIZE_RI, SIZE_S, शून्य, शून्य, शून्य, शून्य, शून्य, शून्यपूर्ण,
	 अणु4000, 4000, 4000, 28000, 0, 0, 0, 0, 0, 0पूर्ण पूर्ण,

	अणुTONE_GERMAN_BUSY,
	 अणुDATA_GA, DATA_S, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्यपूर्ण,
	 अणुSIZE_GA, SIZE_S, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्यपूर्ण,
	 अणु4000, 4000, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण पूर्ण,

	अणुTONE_GERMAN_OLDBUSY,
	 अणुDATA_GO, DATA_S, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्यपूर्ण,
	 अणुSIZE_GO, SIZE_S, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्यपूर्ण,
	 अणु1000, 5000, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण पूर्ण,

	अणुTONE_AMERICAN_BUSY,
	 अणुDATA_BU, DATA_S, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्यपूर्ण,
	 अणुSIZE_BU, SIZE_S, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्यपूर्ण,
	 अणु4000, 4000, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण पूर्ण,

	अणुTONE_GERMAN_HANGUP,
	 अणुDATA_GA, DATA_S, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्यपूर्ण,
	 अणुSIZE_GA, SIZE_S, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्यपूर्ण,
	 अणु4000, 4000, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण पूर्ण,

	अणुTONE_GERMAN_OLDHANGUP,
	 अणुDATA_GO, DATA_S, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्यपूर्ण,
	 अणुSIZE_GO, SIZE_S, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्यपूर्ण,
	 अणु1000, 5000, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण पूर्ण,

	अणुTONE_AMERICAN_HANGUP,
	 अणुDATA_DT, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्यपूर्ण,
	 अणुSIZE_DT, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्यपूर्ण,
	 अणु8000, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण पूर्ण,

	अणुTONE_SPECIAL_INFO,
	 अणुDATA_S1, DATA_S2, DATA_S3, DATA_S, शून्य, शून्य, शून्य, शून्य, शून्य, शून्यपूर्ण,
	 अणुSIZE_S1, SIZE_S2, SIZE_S3, SIZE_S, शून्य, शून्य, शून्य, शून्य, शून्य, शून्यपूर्ण,
	 अणु2666, 2666, 2666, 8002, 0, 0, 0, 0, 0, 0पूर्ण पूर्ण,

	अणुTONE_GERMAN_GASSENBESETZT,
	 अणुDATA_GA, DATA_S, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्यपूर्ण,
	 अणुSIZE_GA, SIZE_S, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्यपूर्ण,
	 अणु2000, 2000, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण पूर्ण,

	अणुTONE_GERMAN_AUFSCHALTTON,
	 अणुDATA_GO, DATA_S, DATA_GO, DATA_S, शून्य, शून्य, शून्य, शून्य, शून्य, शून्यपूर्ण,
	 अणुSIZE_GO, SIZE_S, SIZE_GO, SIZE_S, शून्य, शून्य, शून्य, शून्य, शून्य, शून्यपूर्ण,
	 अणु1000, 5000, 1000, 17000, 0, 0, 0, 0, 0, 0पूर्ण पूर्ण,

	अणु0,
	 अणुशून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्यपूर्ण,
	 अणुशून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य, शून्यपूर्ण,
	 अणु0, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण पूर्ण,
पूर्ण;

/******************
 * copy tone data *
 ******************/

/* an sk_buff is generated from the number of samples needed.
 * the count will be changed and may begin from 0 each pattern period.
 * the clue is to precalculate the poपूर्णांकers and legths to use only one
 * स_नकल per function call, or two स_नकल अगर the tone sequence changes.
 *
 * pattern - the type of the pattern
 * count - the sample from the beginning of the pattern (phase)
 * len - the number of bytes
 *
 * वापस - the sk_buff with the sample
 *
 * अगर tones has finished (e.g. knocking tone), dsp->tones is turned off
 */
व्योम dsp_tone_copy(काष्ठा dsp *dsp, u8 *data, पूर्णांक len)
अणु
	पूर्णांक index, count, start, num;
	काष्ठा pattern *pat;
	काष्ठा dsp_tone *tone = &dsp->tone;

	/* अगर we have no tone, we copy silence */
	अगर (!tone->tone) अणु
		स_रखो(data, dsp_silence, len);
		वापस;
	पूर्ण

	/* process pattern */
	pat = (काष्ठा pattern *)tone->pattern;
	/* poपूर्णांकs to the current pattern */
	index = tone->index; /* gives current sequence index */
	count = tone->count; /* gives current sample */

	/* copy sample */
	जबतक (len) अणु
		/* find sample to start with */
		जबतक (42) अणु
			/* wrap around */
			अगर (!pat->seq[index]) अणु
				count = 0;
				index = 0;
			पूर्ण
			/* check अगर we are currently playing this tone */
			अगर (count < pat->seq[index])
				अवरोध;
			अगर (dsp_debug & DEBUG_DSP_TONE)
				prपूर्णांकk(KERN_DEBUG "%s: reaching next sequence "
				       "(index=%d)\n", __func__, index);
			count -= pat->seq[index];
			index++;
		पूर्ण
		/* calculate start and number of samples */
		start = count % (*(pat->siz[index]));
		num = len;
		अगर (num + count > pat->seq[index])
			num = pat->seq[index] - count;
		अगर (num + start > (*(pat->siz[index])))
			num = (*(pat->siz[index])) - start;
		/* copy memory */
		स_नकल(data, pat->data[index] + start, num);
		/* reduce length */
		data += num;
		count += num;
		len -= num;
	पूर्ण
	tone->index = index;
	tone->count = count;

	/* वापस sk_buff */
	वापस;
पूर्ण


/*******************************
 * send HW message to hfc card *
 *******************************/

अटल व्योम
dsp_tone_hw_message(काष्ठा dsp *dsp, u8 *sample, पूर्णांक len)
अणु
	काष्ठा sk_buff *nskb;

	/* unlocking is not required, because we करोn't expect a response */
	nskb = _alloc_mISDN_skb(PH_CONTROL_REQ,
				(len) ? HFC_SPL_LOOP_ON : HFC_SPL_LOOP_OFF, len, sample,
				GFP_ATOMIC);
	अगर (nskb) अणु
		अगर (dsp->ch.peer) अणु
			अगर (dsp->ch.recv(dsp->ch.peer, nskb))
				dev_kमुक्त_skb(nskb);
		पूर्ण अन्यथा
			dev_kमुक्त_skb(nskb);
	पूर्ण
पूर्ण


/*****************
 * समयr expires *
 *****************/
व्योम
dsp_tone_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा dsp *dsp = from_समयr(dsp, t, tone.tl);
	काष्ठा dsp_tone *tone = &dsp->tone;
	काष्ठा pattern *pat = (काष्ठा pattern *)tone->pattern;
	पूर्णांक index = tone->index;

	अगर (!tone->tone)
		वापस;

	index++;
	अगर (!pat->seq[index])
		index = 0;
	tone->index = index;

	/* set next tone */
	अगर (pat->data[index] == DATA_S)
		dsp_tone_hw_message(dsp, शून्य, 0);
	अन्यथा
		dsp_tone_hw_message(dsp, pat->data[index], *(pat->siz[index]));
	/* set समयr */
	tone->tl.expires = jअगरfies + (pat->seq[index] * HZ) / 8000;
	add_समयr(&tone->tl);
पूर्ण


/********************
 * set/release tone *
 ********************/

/*
 * tones are relaized by streaming or by special loop commands अगर supported
 * by hardware. when hardware is used, the patterns will be controlled by
 * समयrs.
 */
पूर्णांक
dsp_tone(काष्ठा dsp *dsp, पूर्णांक tone)
अणु
	काष्ठा pattern *pat;
	पूर्णांक i;
	काष्ठा dsp_tone *tonet = &dsp->tone;

	tonet->software = 0;
	tonet->hardware = 0;

	/* we turn off the tone */
	अगर (!tone) अणु
		अगर (dsp->features.hfc_loops && समयr_pending(&tonet->tl))
			del_समयr(&tonet->tl);
		अगर (dsp->features.hfc_loops)
			dsp_tone_hw_message(dsp, शून्य, 0);
		tonet->tone = 0;
		वापस 0;
	पूर्ण

	pat = शून्य;
	i = 0;
	जबतक (pattern[i].tone) अणु
		अगर (pattern[i].tone == tone) अणु
			pat = &pattern[i];
			अवरोध;
		पूर्ण
		i++;
	पूर्ण
	अगर (!pat) अणु
		prपूर्णांकk(KERN_WARNING "dsp: given tone 0x%x is invalid\n", tone);
		वापस -EINVAL;
	पूर्ण
	अगर (dsp_debug & DEBUG_DSP_TONE)
		prपूर्णांकk(KERN_DEBUG "%s: now starting tone %d (index=%d)\n",
		       __func__, tone, 0);
	tonet->tone = tone;
	tonet->pattern = pat;
	tonet->index = 0;
	tonet->count = 0;

	अगर (dsp->features.hfc_loops) अणु
		tonet->hardware = 1;
		/* set first tone */
		dsp_tone_hw_message(dsp, pat->data[0], *(pat->siz[0]));
		/* set समयr */
		अगर (समयr_pending(&tonet->tl))
			del_समयr(&tonet->tl);
		tonet->tl.expires = jअगरfies + (pat->seq[0] * HZ) / 8000;
		add_समयr(&tonet->tl);
	पूर्ण अन्यथा अणु
		tonet->software = 1;
	पूर्ण

	वापस 0;
पूर्ण
