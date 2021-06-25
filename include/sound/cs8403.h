<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_CS8403_H
#घोषणा __SOUND_CS8403_H

/*
 *  Routines क्रम Cirrus Logic CS8403/CS8404A IEC958 (S/PDIF) Transmitter
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>,
 *		     Takashi Iwai <tiwai@suse.de>
 */

#अगर_घोषित SND_CS8403

#अगर_अघोषित SND_CS8403_DECL
#घोषणा SND_CS8403_DECL अटल
#पूर्ण_अगर
#अगर_अघोषित SND_CS8403_DECODE
#घोषणा SND_CS8403_DECODE snd_cs8403_decode_spdअगर_bits
#पूर्ण_अगर
#अगर_अघोषित SND_CS8403_ENCODE
#घोषणा SND_CS8403_ENCODE snd_cs8403_encode_spdअगर_bits
#पूर्ण_अगर


SND_CS8403_DECL व्योम SND_CS8403_DECODE(काष्ठा snd_aes_iec958 *diga, अचिन्हित अक्षर bits)
अणु
	अगर (bits & 0x01) अणु	/* consumer */
		अगर (!(bits & 0x02))
			diga->status[0] |= IEC958_AES0_NONAUDIO;
		अगर (!(bits & 0x08))
			diga->status[0] |= IEC958_AES0_CON_NOT_COPYRIGHT;
		चयन (bits & 0x10) अणु
		हाल 0x10: diga->status[0] |= IEC958_AES0_CON_EMPHASIS_NONE; अवरोध;
		हाल 0x00: diga->status[0] |= IEC958_AES0_CON_EMPHASIS_5015; अवरोध;
		पूर्ण
		अगर (!(bits & 0x80))
			diga->status[1] |= IEC958_AES1_CON_ORIGINAL;
		चयन (bits & 0x60) अणु
		हाल 0x00: diga->status[1] |= IEC958_AES1_CON_MAGNETIC_ID; अवरोध;
		हाल 0x20: diga->status[1] |= IEC958_AES1_CON_DIGDIGCONV_ID; अवरोध;
		हाल 0x40: diga->status[1] |= IEC958_AES1_CON_LASEROPT_ID; अवरोध;
		हाल 0x60: diga->status[1] |= IEC958_AES1_CON_GENERAL; अवरोध;
		पूर्ण
		चयन (bits & 0x06) अणु
		हाल 0x00: diga->status[3] |= IEC958_AES3_CON_FS_44100; अवरोध;
		हाल 0x02: diga->status[3] |= IEC958_AES3_CON_FS_48000; अवरोध;
		हाल 0x04: diga->status[3] |= IEC958_AES3_CON_FS_32000; अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		diga->status[0] = IEC958_AES0_PROFESSIONAL;
		चयन (bits & 0x18) अणु
		हाल 0x00: diga->status[0] |= IEC958_AES0_PRO_FS_32000; अवरोध;
		हाल 0x10: diga->status[0] |= IEC958_AES0_PRO_FS_44100; अवरोध;
		हाल 0x08: diga->status[0] |= IEC958_AES0_PRO_FS_48000; अवरोध;
		हाल 0x18: diga->status[0] |= IEC958_AES0_PRO_FS_NOTID; अवरोध;
		पूर्ण
		चयन (bits & 0x60) अणु
		हाल 0x20: diga->status[0] |= IEC958_AES0_PRO_EMPHASIS_NONE; अवरोध;
		हाल 0x40: diga->status[0] |= IEC958_AES0_PRO_EMPHASIS_5015; अवरोध;
		हाल 0x00: diga->status[0] |= IEC958_AES0_PRO_EMPHASIS_CCITT; अवरोध;
		हाल 0x60: diga->status[0] |= IEC958_AES0_PRO_EMPHASIS_NOTID; अवरोध;
		पूर्ण
		अगर (bits & 0x80)
			diga->status[1] |= IEC958_AES1_PRO_MODE_STEREOPHONIC;
	पूर्ण
पूर्ण

SND_CS8403_DECL अचिन्हित अक्षर SND_CS8403_ENCODE(काष्ठा snd_aes_iec958 *diga)
अणु
	अचिन्हित अक्षर bits;

	अगर (!(diga->status[0] & IEC958_AES0_PROFESSIONAL)) अणु
		bits = 0x01;	/* consumer mode */
		अगर (diga->status[0] & IEC958_AES0_NONAUDIO)
			bits &= ~0x02;
		अन्यथा
			bits |= 0x02;
		अगर (diga->status[0] & IEC958_AES0_CON_NOT_COPYRIGHT)
			bits &= ~0x08;
		अन्यथा
			bits |= 0x08;
		चयन (diga->status[0] & IEC958_AES0_CON_EMPHASIS) अणु
		शेष:
		हाल IEC958_AES0_CON_EMPHASIS_NONE: bits |= 0x10; अवरोध;
		हाल IEC958_AES0_CON_EMPHASIS_5015: bits |= 0x00; अवरोध;
		पूर्ण
		अगर (diga->status[1] & IEC958_AES1_CON_ORIGINAL)
			bits &= ~0x80;
		अन्यथा
			bits |= 0x80;
		अगर ((diga->status[1] & IEC958_AES1_CON_CATEGORY) == IEC958_AES1_CON_GENERAL)
			bits |= 0x60;
		अन्यथा अणु
			चयन(diga->status[1] & IEC958_AES1_CON_MAGNETIC_MASK) अणु
			हाल IEC958_AES1_CON_MAGNETIC_ID:
				bits |= 0x00; अवरोध;
			हाल IEC958_AES1_CON_DIGDIGCONV_ID:
				bits |= 0x20; अवरोध;
			शेष:
			हाल IEC958_AES1_CON_LASEROPT_ID:
				bits |= 0x40; अवरोध;
			पूर्ण
		पूर्ण
		चयन (diga->status[3] & IEC958_AES3_CON_FS) अणु
		शेष:
		हाल IEC958_AES3_CON_FS_44100: bits |= 0x00; अवरोध;
		हाल IEC958_AES3_CON_FS_48000: bits |= 0x02; अवरोध;
		हाल IEC958_AES3_CON_FS_32000: bits |= 0x04; अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		bits = 0x00;	/* professional mode */
		अगर (diga->status[0] & IEC958_AES0_NONAUDIO)
			bits &= ~0x02;
		अन्यथा
			bits |= 0x02;
		/* CHECKME: I'm not sure about the bit order in val here */
		चयन (diga->status[0] & IEC958_AES0_PRO_FS) अणु
		हाल IEC958_AES0_PRO_FS_32000:	bits |= 0x00; अवरोध;
		हाल IEC958_AES0_PRO_FS_44100:	bits |= 0x10; अवरोध;	/* 44.1kHz */
		हाल IEC958_AES0_PRO_FS_48000:	bits |= 0x08; अवरोध;	/* 48kHz */
		शेष:
		हाल IEC958_AES0_PRO_FS_NOTID: bits |= 0x18; अवरोध;
		पूर्ण
		चयन (diga->status[0] & IEC958_AES0_PRO_EMPHASIS) अणु
		हाल IEC958_AES0_PRO_EMPHASIS_NONE: bits |= 0x20; अवरोध;
		हाल IEC958_AES0_PRO_EMPHASIS_5015: bits |= 0x40; अवरोध;
		हाल IEC958_AES0_PRO_EMPHASIS_CCITT: bits |= 0x00; अवरोध;
		शेष:
		हाल IEC958_AES0_PRO_EMPHASIS_NOTID: bits |= 0x60; अवरोध;
		पूर्ण
		चयन (diga->status[1] & IEC958_AES1_PRO_MODE) अणु
		हाल IEC958_AES1_PRO_MODE_TWO:
		हाल IEC958_AES1_PRO_MODE_STEREOPHONIC: bits |= 0x00; अवरोध;
		शेष: bits |= 0x80; अवरोध;
		पूर्ण
	पूर्ण
	वापस bits;
पूर्ण

#पूर्ण_अगर /* SND_CS8403 */

#अगर_घोषित SND_CS8404

#अगर_अघोषित SND_CS8404_DECL
#घोषणा SND_CS8404_DECL अटल
#पूर्ण_अगर
#अगर_अघोषित SND_CS8404_DECODE
#घोषणा SND_CS8404_DECODE snd_cs8404_decode_spdअगर_bits
#पूर्ण_अगर
#अगर_अघोषित SND_CS8404_ENCODE
#घोषणा SND_CS8404_ENCODE snd_cs8404_encode_spdअगर_bits
#पूर्ण_अगर


SND_CS8404_DECL व्योम SND_CS8404_DECODE(काष्ठा snd_aes_iec958 *diga, अचिन्हित अक्षर bits)
अणु
	अगर (bits & 0x10) अणु	/* consumer */
		अगर (!(bits & 0x20))
			diga->status[0] |= IEC958_AES0_CON_NOT_COPYRIGHT;
		अगर (!(bits & 0x40))
			diga->status[0] |= IEC958_AES0_CON_EMPHASIS_5015;
		अगर (!(bits & 0x80))
			diga->status[1] |= IEC958_AES1_CON_ORIGINAL;
		चयन (bits & 0x03) अणु
		हाल 0x00: diga->status[1] |= IEC958_AES1_CON_DAT; अवरोध;
		हाल 0x03: diga->status[1] |= IEC958_AES1_CON_GENERAL; अवरोध;
		पूर्ण
		चयन (bits & 0x06) अणु
		हाल 0x02: diga->status[3] |= IEC958_AES3_CON_FS_32000; अवरोध;
		हाल 0x04: diga->status[3] |= IEC958_AES3_CON_FS_48000; अवरोध;
		हाल 0x06: diga->status[3] |= IEC958_AES3_CON_FS_44100; अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		diga->status[0] = IEC958_AES0_PROFESSIONAL;
		अगर (!(bits & 0x04))
			diga->status[0] |= IEC958_AES0_NONAUDIO;
		चयन (bits & 0x60) अणु
		हाल 0x00: diga->status[0] |= IEC958_AES0_PRO_FS_32000; अवरोध;
		हाल 0x40: diga->status[0] |= IEC958_AES0_PRO_FS_44100; अवरोध;
		हाल 0x20: diga->status[0] |= IEC958_AES0_PRO_FS_48000; अवरोध;
		हाल 0x60: diga->status[0] |= IEC958_AES0_PRO_FS_NOTID; अवरोध;
		पूर्ण
		चयन (bits & 0x03) अणु
		हाल 0x02: diga->status[0] |= IEC958_AES0_PRO_EMPHASIS_NONE; अवरोध;
		हाल 0x01: diga->status[0] |= IEC958_AES0_PRO_EMPHASIS_5015; अवरोध;
		हाल 0x00: diga->status[0] |= IEC958_AES0_PRO_EMPHASIS_CCITT; अवरोध;
		हाल 0x03: diga->status[0] |= IEC958_AES0_PRO_EMPHASIS_NOTID; अवरोध;
		पूर्ण
		अगर (!(bits & 0x80))
			diga->status[1] |= IEC958_AES1_PRO_MODE_STEREOPHONIC;
	पूर्ण
पूर्ण

SND_CS8404_DECL अचिन्हित अक्षर SND_CS8404_ENCODE(काष्ठा snd_aes_iec958 *diga)
अणु
	अचिन्हित अक्षर bits;

	अगर (!(diga->status[0] & IEC958_AES0_PROFESSIONAL)) अणु
		bits = 0x10;	/* consumer mode */
		अगर (!(diga->status[0] & IEC958_AES0_CON_NOT_COPYRIGHT))
			bits |= 0x20;
		अगर ((diga->status[0] & IEC958_AES0_CON_EMPHASIS) == IEC958_AES0_CON_EMPHASIS_NONE)
			bits |= 0x40;
		अगर (!(diga->status[1] & IEC958_AES1_CON_ORIGINAL))
			bits |= 0x80;
		अगर ((diga->status[1] & IEC958_AES1_CON_CATEGORY) == IEC958_AES1_CON_GENERAL)
			bits |= 0x03;
		चयन (diga->status[3] & IEC958_AES3_CON_FS) अणु
		शेष:
		हाल IEC958_AES3_CON_FS_44100: bits |= 0x06; अवरोध;
		हाल IEC958_AES3_CON_FS_48000: bits |= 0x04; अवरोध;
		हाल IEC958_AES3_CON_FS_32000: bits |= 0x02; अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		bits = 0x00;	/* professional mode */
		अगर (!(diga->status[0] & IEC958_AES0_NONAUDIO))
			bits |= 0x04;
		चयन (diga->status[0] & IEC958_AES0_PRO_FS) अणु
		हाल IEC958_AES0_PRO_FS_32000:	bits |= 0x00; अवरोध;
		हाल IEC958_AES0_PRO_FS_44100:	bits |= 0x40; अवरोध;	/* 44.1kHz */
		हाल IEC958_AES0_PRO_FS_48000:	bits |= 0x20; अवरोध;	/* 48kHz */
		शेष:
		हाल IEC958_AES0_PRO_FS_NOTID:	bits |= 0x00; अवरोध;
		पूर्ण
		चयन (diga->status[0] & IEC958_AES0_PRO_EMPHASIS) अणु
		हाल IEC958_AES0_PRO_EMPHASIS_NONE: bits |= 0x02; अवरोध;
		हाल IEC958_AES0_PRO_EMPHASIS_5015: bits |= 0x01; अवरोध;
		हाल IEC958_AES0_PRO_EMPHASIS_CCITT: bits |= 0x00; अवरोध;
		शेष:
		हाल IEC958_AES0_PRO_EMPHASIS_NOTID: bits |= 0x03; अवरोध;
		पूर्ण
		चयन (diga->status[1] & IEC958_AES1_PRO_MODE) अणु
		हाल IEC958_AES1_PRO_MODE_TWO:
		हाल IEC958_AES1_PRO_MODE_STEREOPHONIC: bits |= 0x00; अवरोध;
		शेष: bits |= 0x80; अवरोध;
		पूर्ण
	पूर्ण
	वापस bits;
पूर्ण

#पूर्ण_अगर /* SND_CS8404 */

#पूर्ण_अगर /* __SOUND_CS8403_H */
