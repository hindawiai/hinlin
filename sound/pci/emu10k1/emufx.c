<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *                   Creative Lअसल, Inc.
 *  Routines क्रम effect processor FX8010
 *
 *  Copyright (c) by James Courtier-Dutton <James@superbug.co.uk>
 *  	Added EMU 1010 support.
 *
 *  BUGS:
 *    --
 *
 *  TODO:
 *    --
 */

#समावेश <linux/pci.h>
#समावेश <linux/capability.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/init.h>
#समावेश <linux/mutex.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/nospec.h>

#समावेश <sound/core.h>
#समावेश <sound/tlv.h>
#समावेश <sound/emu10k1.h>

#अगर 0		/* क्रम testing purposes - digital out -> capture */
#घोषणा EMU10K1_CAPTURE_DIGITAL_OUT
#पूर्ण_अगर
#अगर 0		/* क्रम testing purposes - set S/PDIF to AC3 output */
#घोषणा EMU10K1_SET_AC3_IEC958
#पूर्ण_अगर
#अगर 0		/* क्रम testing purposes - feed the front संकेत to Center/LFE outमाला_दो */
#घोषणा EMU10K1_CENTER_LFE_FROM_FRONT
#पूर्ण_अगर

अटल bool high_res_gpr_volume;
module_param(high_res_gpr_volume, bool, 0444);
MODULE_PARM_DESC(high_res_gpr_volume, "GPR mixer controls use 31-bit range.");

/*
 *  Tables
 */ 

अटल स्थिर अक्षर * स्थिर fxbuses[16] = अणु
	/* 0x00 */ "PCM Left",
	/* 0x01 */ "PCM Right",
	/* 0x02 */ "PCM Surround Left",
	/* 0x03 */ "PCM Surround Right",
	/* 0x04 */ "MIDI Left",
	/* 0x05 */ "MIDI Right",
	/* 0x06 */ "Center",
	/* 0x07 */ "LFE",
	/* 0x08 */ शून्य,
	/* 0x09 */ शून्य,
	/* 0x0a */ शून्य,
	/* 0x0b */ शून्य,
	/* 0x0c */ "MIDI Reverb",
	/* 0x0d */ "MIDI Chorus",
	/* 0x0e */ शून्य,
	/* 0x0f */ शून्य
पूर्ण;

अटल स्थिर अक्षर * स्थिर creative_ins[16] = अणु
	/* 0x00 */ "AC97 Left",
	/* 0x01 */ "AC97 Right",
	/* 0x02 */ "TTL IEC958 Left",
	/* 0x03 */ "TTL IEC958 Right",
	/* 0x04 */ "Zoom Video Left",
	/* 0x05 */ "Zoom Video Right",
	/* 0x06 */ "Optical IEC958 Left",
	/* 0x07 */ "Optical IEC958 Right",
	/* 0x08 */ "Line/Mic 1 Left",
	/* 0x09 */ "Line/Mic 1 Right",
	/* 0x0a */ "Coaxial IEC958 Left",
	/* 0x0b */ "Coaxial IEC958 Right",
	/* 0x0c */ "Line/Mic 2 Left",
	/* 0x0d */ "Line/Mic 2 Right",
	/* 0x0e */ शून्य,
	/* 0x0f */ शून्य
पूर्ण;

अटल स्थिर अक्षर * स्थिर audigy_ins[16] = अणु
	/* 0x00 */ "AC97 Left",
	/* 0x01 */ "AC97 Right",
	/* 0x02 */ "Audigy CD Left",
	/* 0x03 */ "Audigy CD Right",
	/* 0x04 */ "Optical IEC958 Left",
	/* 0x05 */ "Optical IEC958 Right",
	/* 0x06 */ शून्य,
	/* 0x07 */ शून्य,
	/* 0x08 */ "Line/Mic 2 Left",
	/* 0x09 */ "Line/Mic 2 Right",
	/* 0x0a */ "SPDIF Left",
	/* 0x0b */ "SPDIF Right",
	/* 0x0c */ "Aux2 Left",
	/* 0x0d */ "Aux2 Right",
	/* 0x0e */ शून्य,
	/* 0x0f */ शून्य
पूर्ण;

अटल स्थिर अक्षर * स्थिर creative_outs[32] = अणु
	/* 0x00 */ "AC97 Left",
	/* 0x01 */ "AC97 Right",
	/* 0x02 */ "Optical IEC958 Left",
	/* 0x03 */ "Optical IEC958 Right",
	/* 0x04 */ "Center",
	/* 0x05 */ "LFE",
	/* 0x06 */ "Headphone Left",
	/* 0x07 */ "Headphone Right",
	/* 0x08 */ "Surround Left",
	/* 0x09 */ "Surround Right",
	/* 0x0a */ "PCM Capture Left",
	/* 0x0b */ "PCM Capture Right",
	/* 0x0c */ "MIC Capture",
	/* 0x0d */ "AC97 Surround Left",
	/* 0x0e */ "AC97 Surround Right",
	/* 0x0f */ शून्य,
	/* 0x10 */ शून्य,
	/* 0x11 */ "Analog Center",
	/* 0x12 */ "Analog LFE",
	/* 0x13 */ शून्य,
	/* 0x14 */ शून्य,
	/* 0x15 */ शून्य,
	/* 0x16 */ शून्य,
	/* 0x17 */ शून्य,
	/* 0x18 */ शून्य,
	/* 0x19 */ शून्य,
	/* 0x1a */ शून्य,
	/* 0x1b */ शून्य,
	/* 0x1c */ शून्य,
	/* 0x1d */ शून्य,
	/* 0x1e */ शून्य,
	/* 0x1f */ शून्य,
पूर्ण;

अटल स्थिर अक्षर * स्थिर audigy_outs[32] = अणु
	/* 0x00 */ "Digital Front Left",
	/* 0x01 */ "Digital Front Right",
	/* 0x02 */ "Digital Center",
	/* 0x03 */ "Digital LEF",
	/* 0x04 */ "Headphone Left",
	/* 0x05 */ "Headphone Right",
	/* 0x06 */ "Digital Rear Left",
	/* 0x07 */ "Digital Rear Right",
	/* 0x08 */ "Front Left",
	/* 0x09 */ "Front Right",
	/* 0x0a */ "Center",
	/* 0x0b */ "LFE",
	/* 0x0c */ शून्य,
	/* 0x0d */ शून्य,
	/* 0x0e */ "Rear Left",
	/* 0x0f */ "Rear Right",
	/* 0x10 */ "AC97 Front Left",
	/* 0x11 */ "AC97 Front Right",
	/* 0x12 */ "ADC Capture Left",
	/* 0x13 */ "ADC Capture Right",
	/* 0x14 */ शून्य,
	/* 0x15 */ शून्य,
	/* 0x16 */ शून्य,
	/* 0x17 */ शून्य,
	/* 0x18 */ शून्य,
	/* 0x19 */ शून्य,
	/* 0x1a */ शून्य,
	/* 0x1b */ शून्य,
	/* 0x1c */ शून्य,
	/* 0x1d */ शून्य,
	/* 0x1e */ शून्य,
	/* 0x1f */ शून्य,
पूर्ण;

अटल स्थिर u32 bass_table[41][5] = अणु
	अणु 0x3e4f844f, 0x84ed4cc3, 0x3cc69927, 0x7b03553a, 0xc4da8486 पूर्ण,
	अणु 0x3e69a17a, 0x84c280fb, 0x3cd77cd4, 0x7b2f2a6f, 0xc4b08d1d पूर्ण,
	अणु 0x3e82ff42, 0x849991d5, 0x3ce7466b, 0x7b5917c6, 0xc48863ee पूर्ण,
	अणु 0x3e9bab3c, 0x847267f0, 0x3cf5ffe8, 0x7b813560, 0xc461f22c पूर्ण,
	अणु 0x3eb3b275, 0x844ced29, 0x3d03b295, 0x7ba79a1c, 0xc43d223b पूर्ण,
	अणु 0x3ecb2174, 0x84290c8b, 0x3d106714, 0x7bcc5ba3, 0xc419dfa5 पूर्ण,
	अणु 0x3ee2044b, 0x8406b244, 0x3d1c2561, 0x7bef8e77, 0xc3f8170f पूर्ण,
	अणु 0x3ef86698, 0x83e5cb96, 0x3d26f4d8, 0x7c114600, 0xc3d7b625 पूर्ण,
	अणु 0x3f0e5390, 0x83c646c9, 0x3d30dc39, 0x7c319498, 0xc3b8ab97 पूर्ण,
	अणु 0x3f23d60b, 0x83a81321, 0x3d39e1af, 0x7c508b9c, 0xc39ae704 पूर्ण,
	अणु 0x3f38f884, 0x838b20d2, 0x3d420ad2, 0x7c6e3b75, 0xc37e58f1 पूर्ण,
	अणु 0x3f4dc52c, 0x836f60ef, 0x3d495cab, 0x7c8ab3a6, 0xc362f2be पूर्ण,
	अणु 0x3f6245e8, 0x8354c565, 0x3d4fdbb8, 0x7ca602d6, 0xc348a69b पूर्ण,
	अणु 0x3f76845f, 0x833b40ec, 0x3d558bf0, 0x7cc036df, 0xc32f677c पूर्ण,
	अणु 0x3f8a8a03, 0x8322c6fb, 0x3d5a70c4, 0x7cd95cd7, 0xc317290b पूर्ण,
	अणु 0x3f9e6014, 0x830b4bc3, 0x3d5e8d25, 0x7cf1811a, 0xc2ffdfa5 पूर्ण,
	अणु 0x3fb20fae, 0x82f4c420, 0x3d61e37f, 0x7d08af56, 0xc2e9804a पूर्ण,
	अणु 0x3fc5a1cc, 0x82df2592, 0x3d6475c3, 0x7d1ef294, 0xc2d40096 पूर्ण,
	अणु 0x3fd91f55, 0x82ca6632, 0x3d664564, 0x7d345541, 0xc2bf56b9 पूर्ण,
	अणु 0x3fec9120, 0x82b67cac, 0x3d675356, 0x7d48e138, 0xc2ab796e पूर्ण,
	अणु 0x40000000, 0x82a36037, 0x3d67a012, 0x7d5c9fc9, 0xc2985fee पूर्ण,
	अणु 0x401374c7, 0x8291088a, 0x3d672b93, 0x7d6f99c3, 0xc28601f2 पूर्ण,
	अणु 0x4026f857, 0x827f6dd7, 0x3d65f559, 0x7d81d77c, 0xc27457a3 पूर्ण,
	अणु 0x403a939f, 0x826e88c5, 0x3d63fc63, 0x7d9360d4, 0xc2635996 पूर्ण,
	अणु 0x404e4faf, 0x825e5266, 0x3d613f32, 0x7da43d42, 0xc25300c6 पूर्ण,
	अणु 0x406235ba, 0x824ec434, 0x3d5dbbc3, 0x7db473d7, 0xc243468e पूर्ण,
	अणु 0x40764f1f, 0x823fd80c, 0x3d596f8f, 0x7dc40b44, 0xc23424a2 पूर्ण,
	अणु 0x408aa576, 0x82318824, 0x3d545787, 0x7dd309e2, 0xc2259509 पूर्ण,
	अणु 0x409f4296, 0x8223cf0b, 0x3d4e7012, 0x7de175b5, 0xc2179218 पूर्ण,
	अणु 0x40b430a0, 0x8216a7a1, 0x3d47b505, 0x7def5475, 0xc20a1670 पूर्ण,
	अणु 0x40c97a0a, 0x820a0d12, 0x3d4021a1, 0x7dfcab8d, 0xc1fd1cf5 पूर्ण,
	अणु 0x40df29a6, 0x81fdfad6, 0x3d37b08d, 0x7e098028, 0xc1f0a0ca पूर्ण,
	अणु 0x40f54ab1, 0x81f26ca9, 0x3d2e5bd1, 0x7e15d72b, 0xc1e49d52 पूर्ण,
	अणु 0x410be8da, 0x81e75e89, 0x3d241cce, 0x7e21b544, 0xc1d90e24 पूर्ण,
	अणु 0x41231051, 0x81dcccb3, 0x3d18ec37, 0x7e2d1ee6, 0xc1cdef10 पूर्ण,
	अणु 0x413acdd0, 0x81d2b39e, 0x3d0cc20a, 0x7e38184e, 0xc1c33c13 पूर्ण,
	अणु 0x41532ea7, 0x81c90ffb, 0x3cff9585, 0x7e42a58b, 0xc1b8f15a पूर्ण,
	अणु 0x416c40cd, 0x81bfdeb2, 0x3cf15d21, 0x7e4cca7c, 0xc1af0b3f पूर्ण,
	अणु 0x418612ea, 0x81b71cdc, 0x3ce20e85, 0x7e568ad3, 0xc1a58640 पूर्ण,
	अणु 0x41a0b465, 0x81aec7c5, 0x3cd19e7c, 0x7e5fea1e, 0xc19c5f03 पूर्ण,
	अणु 0x41bc3573, 0x81a6dcea, 0x3cc000e9, 0x7e68ebc2, 0xc1939250 पूर्ण
पूर्ण;

अटल स्थिर u32 treble_table[41][5] = अणु
	अणु 0x0125cba9, 0xfed5debd, 0x00599b6c, 0x0d2506da, 0xfa85b354 पूर्ण,
	अणु 0x0142f67e, 0xfeb03163, 0x0066cd0f, 0x0d14c69d, 0xfa914473 पूर्ण,
	अणु 0x016328bd, 0xfe860158, 0x0075b7f2, 0x0d03eb27, 0xfa9d32d2 पूर्ण,
	अणु 0x0186b438, 0xfe56c982, 0x00869234, 0x0cf27048, 0xfaa97fca पूर्ण,
	अणु 0x01adf358, 0xfe21f5fe, 0x00999842, 0x0ce051c2, 0xfab62ca5 पूर्ण,
	अणु 0x01d949fa, 0xfde6e287, 0x00af0d8d, 0x0ccd8b4a, 0xfac33aa7 पूर्ण,
	अणु 0x02092669, 0xfda4d8bf, 0x00c73d4c, 0x0cba1884, 0xfad0ab07 पूर्ण,
	अणु 0x023e0268, 0xfd5b0e4a, 0x00e27b54, 0x0ca5f509, 0xfade7ef2 पूर्ण,
	अणु 0x0278645c, 0xfd08a2b0, 0x01012509, 0x0c911c63, 0xfaecb788 पूर्ण,
	अणु 0x02b8e091, 0xfcac9d1a, 0x0123a262, 0x0c7b8a14, 0xfafb55df पूर्ण,
	अणु 0x03001a9a, 0xfc45e9ce, 0x014a6709, 0x0c65398f, 0xfb0a5aff पूर्ण,
	अणु 0x034ec6d7, 0xfbd3576b, 0x0175f397, 0x0c4e2643, 0xfb19c7e4 पूर्ण,
	अणु 0x03a5ac15, 0xfb5393ee, 0x01a6d6ed, 0x0c364b94, 0xfb299d7c पूर्ण,
	अणु 0x0405a562, 0xfac52968, 0x01ddafae, 0x0c1da4e2, 0xfb39dca5 पूर्ण,
	अणु 0x046fa3fe, 0xfa267a66, 0x021b2ddd, 0x0c042d8d, 0xfb4a8631 पूर्ण,
	अणु 0x04e4b17f, 0xf975be0f, 0x0260149f, 0x0be9e0f2, 0xfb5b9ae0 पूर्ण,
	अणु 0x0565f220, 0xf8b0fbe5, 0x02ad3c29, 0x0bceba73, 0xfb6d1b60 पूर्ण,
	अणु 0x05f4a745, 0xf7d60722, 0x030393d4, 0x0bb2b578, 0xfb7f084d पूर्ण,
	अणु 0x06923236, 0xf6e279bd, 0x03642465, 0x0b95cd75, 0xfb916233 पूर्ण,
	अणु 0x07401713, 0xf5d3aef9, 0x03d01283, 0x0b77fded, 0xfba42984 पूर्ण,
	अणु 0x08000000, 0xf4a6bd88, 0x0448a161, 0x0b594278, 0xfbb75e9f पूर्ण,
	अणु 0x08d3c097, 0xf3587131, 0x04cf35a4, 0x0b3996c9, 0xfbcb01cb पूर्ण,
	अणु 0x09bd59a2, 0xf1e543f9, 0x05655880, 0x0b18f6b2, 0xfbdf1333 पूर्ण,
	अणु 0x0abefd0f, 0xf04956ca, 0x060cbb12, 0x0af75e2c, 0xfbf392e8 पूर्ण,
	अणु 0x0bdb123e, 0xee806984, 0x06c739fe, 0x0ad4c962, 0xfc0880dd पूर्ण,
	अणु 0x0d143a94, 0xec85d287, 0x0796e150, 0x0ab134b0, 0xfc1ddce5 पूर्ण,
	अणु 0x0e6d5664, 0xea547598, 0x087df0a0, 0x0a8c9cb6, 0xfc33a6ad पूर्ण,
	अणु 0x0fe98a2a, 0xe7e6ba35, 0x097edf83, 0x0a66fe5b, 0xfc49ddc2 पूर्ण,
	अणु 0x118c4421, 0xe536813a, 0x0a9c6248, 0x0a4056d7, 0xfc608185 पूर्ण,
	अणु 0x1359422e, 0xe23d19eb, 0x0bd96efb, 0x0a18a3bf, 0xfc77912c पूर्ण,
	अणु 0x1554982b, 0xdef33645, 0x0d3942bd, 0x09efe312, 0xfc8f0bc1 पूर्ण,
	अणु 0x1782b68a, 0xdb50deb1, 0x0ebf676d, 0x09c6133f, 0xfca6f019 पूर्ण,
	अणु 0x19e8715d, 0xd74d64fd, 0x106fb999, 0x099b3337, 0xfcbf3cd6 पूर्ण,
	अणु 0x1c8b07b8, 0xd2df56ab, 0x124e6ec8, 0x096f4274, 0xfcd7f060 पूर्ण,
	अणु 0x1f702b6d, 0xcdfc6e92, 0x14601c10, 0x0942410b, 0xfcf108e5 पूर्ण,
	अणु 0x229e0933, 0xc89985cd, 0x16a9bcfa, 0x09142fb5, 0xfd0a8451 पूर्ण,
	अणु 0x261b5118, 0xc2aa8409, 0x1930bab6, 0x08e50fdc, 0xfd24604d पूर्ण,
	अणु 0x29ef3f5d, 0xbc224f28, 0x1bfaf396, 0x08b4e3aa, 0xfd3e9a3b पूर्ण,
	अणु 0x2e21a59b, 0xb4f2ba46, 0x1f0ec2d6, 0x0883ae15, 0xfd592f33 पूर्ण,
	अणु 0x32baf44b, 0xad0c7429, 0x227308a3, 0x085172eb, 0xfd741bfd पूर्ण,
	अणु 0x37c4448b, 0xa45ef51d, 0x262f3267, 0x081e36dc, 0xfd8f5d14 पूर्ण
पूर्ण;

/* dB gain = (भग्न) 20 * log10( भग्न(db_table_value) / 0x8000000 ) */
अटल स्थिर u32 db_table[101] = अणु
	0x00000000, 0x01571f82, 0x01674b41, 0x01783a1b, 0x0189f540,
	0x019c8651, 0x01aff763, 0x01c45306, 0x01d9a446, 0x01eff6b8,
	0x0207567a, 0x021fd03d, 0x0239714c, 0x02544792, 0x027061a1,
	0x028dcebb, 0x02ac9edc, 0x02cce2bf, 0x02eeabe8, 0x03120cb0,
	0x0337184e, 0x035de2df, 0x03868173, 0x03b10a18, 0x03dd93e9,
	0x040c3713, 0x043d0cea, 0x04702ff3, 0x04a5bbf2, 0x04ddcdfb,
	0x0518847f, 0x0555ff62, 0x05966005, 0x05d9c95d, 0x06206005,
	0x066a4a52, 0x06b7b067, 0x0708bc4c, 0x075d9a01, 0x07b6779d,
	0x08138561, 0x0874f5d5, 0x08dafde1, 0x0945d4ed, 0x09b5b4fd,
	0x0a2adad1, 0x0aa58605, 0x0b25f936, 0x0bac7a24, 0x0c3951d8,
	0x0ccccccc, 0x0d673b17, 0x0e08f093, 0x0eb24510, 0x0f639481,
	0x101d3f2d, 0x10dfa9e6, 0x11ab3e3f, 0x12806ac3, 0x135fa333,
	0x144960c5, 0x153e2266, 0x163e6cfe, 0x174acbb7, 0x1863d04d,
	0x198a1357, 0x1abe349f, 0x1c00db77, 0x1d52b712, 0x1eb47ee6,
	0x2026f30f, 0x21aadcb6, 0x23410e7e, 0x24ea64f9, 0x26a7c71d,
	0x287a26c4, 0x2a62812c, 0x2c61df84, 0x2e795779, 0x30aa0bcf,
	0x32f52cfe, 0x355bf9d8, 0x37dfc033, 0x3a81dda4, 0x3d43c038,
	0x4026e73c, 0x432ce40f, 0x46575af8, 0x49a8040f, 0x4d20ac2a,
	0x50c335d3, 0x54919a57, 0x588dead1, 0x5cba514a, 0x611911ea,
	0x65ac8c2f, 0x6a773c39, 0x6f7bbc23, 0x74bcc56c, 0x7a3d3272,
	0x7fffffff,
पूर्ण;

/* EMU10k1/EMU10k2 DSP control db gain */
अटल स्थिर DECLARE_TLV_DB_SCALE(snd_emu10k1_db_scale1, -4000, 40, 1);
अटल स्थिर DECLARE_TLV_DB_LINEAR(snd_emu10k1_db_linear, TLV_DB_GAIN_MUTE, 0);

/* EMU10K1 bass/treble db gain */
अटल स्थिर DECLARE_TLV_DB_SCALE(snd_emu10k1_bass_treble_db_scale, -1200, 60, 0);

अटल स्थिर u32 onoff_table[2] = अणु
	0x00000000, 0x00000001
पूर्ण;

/*
 *   controls
 */

अटल पूर्णांक snd_emu10k1_gpr_ctl_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा snd_emu10k1_fx8010_ctl *ctl =
		(काष्ठा snd_emu10k1_fx8010_ctl *) kcontrol->निजी_value;

	अगर (ctl->min == 0 && ctl->max == 1)
		uinfo->type = SNDRV_CTL_ELEM_TYPE_BOOLEAN;
	अन्यथा
		uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = ctl->vcount;
	uinfo->value.पूर्णांकeger.min = ctl->min;
	uinfo->value.पूर्णांकeger.max = ctl->max;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1_gpr_ctl_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_emu10k1_fx8010_ctl *ctl =
		(काष्ठा snd_emu10k1_fx8010_ctl *) kcontrol->निजी_value;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;
	
	spin_lock_irqsave(&emu->reg_lock, flags);
	क्रम (i = 0; i < ctl->vcount; i++)
		ucontrol->value.पूर्णांकeger.value[i] = ctl->value[i];
	spin_unlock_irqrestore(&emu->reg_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1_gpr_ctl_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_emu10k1_fx8010_ctl *ctl =
		(काष्ठा snd_emu10k1_fx8010_ctl *) kcontrol->निजी_value;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक nval, val;
	अचिन्हित पूर्णांक i, j;
	पूर्णांक change = 0;
	
	spin_lock_irqsave(&emu->reg_lock, flags);
	क्रम (i = 0; i < ctl->vcount; i++) अणु
		nval = ucontrol->value.पूर्णांकeger.value[i];
		अगर (nval < ctl->min)
			nval = ctl->min;
		अगर (nval > ctl->max)
			nval = ctl->max;
		अगर (nval != ctl->value[i])
			change = 1;
		val = ctl->value[i] = nval;
		चयन (ctl->translation) अणु
		हाल EMU10K1_GPR_TRANSLATION_NONE:
			snd_emu10k1_ptr_ग_लिखो(emu, emu->gpr_base + ctl->gpr[i], 0, val);
			अवरोध;
		हाल EMU10K1_GPR_TRANSLATION_TABLE100:
			snd_emu10k1_ptr_ग_लिखो(emu, emu->gpr_base + ctl->gpr[i], 0, db_table[val]);
			अवरोध;
		हाल EMU10K1_GPR_TRANSLATION_BASS:
			अगर ((ctl->count % 5) != 0 || (ctl->count / 5) != ctl->vcount) अणु
				change = -EIO;
				जाओ __error;
			पूर्ण
			क्रम (j = 0; j < 5; j++)
				snd_emu10k1_ptr_ग_लिखो(emu, emu->gpr_base + ctl->gpr[j * ctl->vcount + i], 0, bass_table[val][j]);
			अवरोध;
		हाल EMU10K1_GPR_TRANSLATION_TREBLE:
			अगर ((ctl->count % 5) != 0 || (ctl->count / 5) != ctl->vcount) अणु
				change = -EIO;
				जाओ __error;
			पूर्ण
			क्रम (j = 0; j < 5; j++)
				snd_emu10k1_ptr_ग_लिखो(emu, emu->gpr_base + ctl->gpr[j * ctl->vcount + i], 0, treble_table[val][j]);
			अवरोध;
		हाल EMU10K1_GPR_TRANSLATION_ONOFF:
			snd_emu10k1_ptr_ग_लिखो(emu, emu->gpr_base + ctl->gpr[i], 0, onoff_table[val]);
			अवरोध;
		पूर्ण
	पूर्ण
      __error:
	spin_unlock_irqrestore(&emu->reg_lock, flags);
	वापस change;
पूर्ण

/*
 *   Interrupt handler
 */

अटल व्योम snd_emu10k1_fx8010_पूर्णांकerrupt(काष्ठा snd_emu10k1 *emu)
अणु
	काष्ठा snd_emu10k1_fx8010_irq *irq, *nirq;

	irq = emu->fx8010.irq_handlers;
	जबतक (irq) अणु
		nirq = irq->next;	/* irq ptr can be हटाओd from list */
		अगर (snd_emu10k1_ptr_पढ़ो(emu, emu->gpr_base + irq->gpr_running, 0) & 0xffff0000) अणु
			अगर (irq->handler)
				irq->handler(emu, irq->निजी_data);
			snd_emu10k1_ptr_ग_लिखो(emu, emu->gpr_base + irq->gpr_running, 0, 1);
		पूर्ण
		irq = nirq;
	पूर्ण
पूर्ण

पूर्णांक snd_emu10k1_fx8010_रेजिस्टर_irq_handler(काष्ठा snd_emu10k1 *emu,
					    snd_fx8010_irq_handler_t *handler,
					    अचिन्हित अक्षर gpr_running,
					    व्योम *निजी_data,
					    काष्ठा snd_emu10k1_fx8010_irq *irq)
अणु
	अचिन्हित दीर्घ flags;
	
	irq->handler = handler;
	irq->gpr_running = gpr_running;
	irq->निजी_data = निजी_data;
	irq->next = शून्य;
	spin_lock_irqsave(&emu->fx8010.irq_lock, flags);
	अगर (emu->fx8010.irq_handlers == शून्य) अणु
		emu->fx8010.irq_handlers = irq;
		emu->dsp_पूर्णांकerrupt = snd_emu10k1_fx8010_पूर्णांकerrupt;
		snd_emu10k1_पूर्णांकr_enable(emu, INTE_FXDSPENABLE);
	पूर्ण अन्यथा अणु
		irq->next = emu->fx8010.irq_handlers;
		emu->fx8010.irq_handlers = irq;
	पूर्ण
	spin_unlock_irqrestore(&emu->fx8010.irq_lock, flags);
	वापस 0;
पूर्ण

पूर्णांक snd_emu10k1_fx8010_unरेजिस्टर_irq_handler(काष्ठा snd_emu10k1 *emu,
					      काष्ठा snd_emu10k1_fx8010_irq *irq)
अणु
	काष्ठा snd_emu10k1_fx8010_irq *पंचांगp;
	अचिन्हित दीर्घ flags;
	
	spin_lock_irqsave(&emu->fx8010.irq_lock, flags);
	अगर ((पंचांगp = emu->fx8010.irq_handlers) == irq) अणु
		emu->fx8010.irq_handlers = पंचांगp->next;
		अगर (emu->fx8010.irq_handlers == शून्य) अणु
			snd_emu10k1_पूर्णांकr_disable(emu, INTE_FXDSPENABLE);
			emu->dsp_पूर्णांकerrupt = शून्य;
		पूर्ण
	पूर्ण अन्यथा अणु
		जबतक (पंचांगp && पंचांगp->next != irq)
			पंचांगp = पंचांगp->next;
		अगर (पंचांगp)
			पंचांगp->next = पंचांगp->next->next;
	पूर्ण
	spin_unlock_irqrestore(&emu->fx8010.irq_lock, flags);
	वापस 0;
पूर्ण

/*************************************************************************
 * EMU10K1 effect manager
 *************************************************************************/

अटल व्योम snd_emu10k1_ग_लिखो_op(काष्ठा snd_emu10k1_fx8010_code *icode,
				 अचिन्हित पूर्णांक *ptr,
				 u32 op, u32 r, u32 a, u32 x, u32 y)
अणु
	u_पूर्णांक32_t *code;
	अगर (snd_BUG_ON(*ptr >= 512))
		वापस;
	code = icode->code + (*ptr) * 2;
	set_bit(*ptr, icode->code_valid);
	code[0] = ((x & 0x3ff) << 10) | (y & 0x3ff);
	code[1] = ((op & 0x0f) << 20) | ((r & 0x3ff) << 10) | (a & 0x3ff);
	(*ptr)++;
पूर्ण

#घोषणा OP(icode, ptr, op, r, a, x, y) \
	snd_emu10k1_ग_लिखो_op(icode, ptr, op, r, a, x, y)

अटल व्योम snd_emu10k1_audigy_ग_लिखो_op(काष्ठा snd_emu10k1_fx8010_code *icode,
					अचिन्हित पूर्णांक *ptr,
					u32 op, u32 r, u32 a, u32 x, u32 y)
अणु
	u_पूर्णांक32_t *code;
	अगर (snd_BUG_ON(*ptr >= 1024))
		वापस;
	code = icode->code + (*ptr) * 2;
	set_bit(*ptr, icode->code_valid);
	code[0] = ((x & 0x7ff) << 12) | (y & 0x7ff);
	code[1] = ((op & 0x0f) << 24) | ((r & 0x7ff) << 12) | (a & 0x7ff);
	(*ptr)++;
पूर्ण

#घोषणा A_OP(icode, ptr, op, r, a, x, y) \
	snd_emu10k1_audigy_ग_लिखो_op(icode, ptr, op, r, a, x, y)

अटल व्योम snd_emu10k1_efx_ग_लिखो(काष्ठा snd_emu10k1 *emu, अचिन्हित पूर्णांक pc, अचिन्हित पूर्णांक data)
अणु
	pc += emu->audigy ? A_MICROCODEBASE : MICROCODEBASE;
	snd_emu10k1_ptr_ग_लिखो(emu, pc, 0, data);
पूर्ण

अचिन्हित पूर्णांक snd_emu10k1_efx_पढ़ो(काष्ठा snd_emu10k1 *emu, अचिन्हित पूर्णांक pc)
अणु
	pc += emu->audigy ? A_MICROCODEBASE : MICROCODEBASE;
	वापस snd_emu10k1_ptr_पढ़ो(emu, pc, 0);
पूर्ण

अटल पूर्णांक snd_emu10k1_gpr_poke(काष्ठा snd_emu10k1 *emu,
				काष्ठा snd_emu10k1_fx8010_code *icode,
				bool in_kernel)
अणु
	पूर्णांक gpr;
	u32 val;

	क्रम (gpr = 0; gpr < (emu->audigy ? 0x200 : 0x100); gpr++) अणु
		अगर (!test_bit(gpr, icode->gpr_valid))
			जारी;
		अगर (in_kernel)
			val = icode->gpr_map[gpr];
		अन्यथा अगर (get_user(val, (__user u32 *)&icode->gpr_map[gpr]))
			वापस -EFAULT;
		snd_emu10k1_ptr_ग_लिखो(emu, emu->gpr_base + gpr, 0, val);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1_gpr_peek(काष्ठा snd_emu10k1 *emu,
				काष्ठा snd_emu10k1_fx8010_code *icode)
अणु
	पूर्णांक gpr;
	u32 val;

	क्रम (gpr = 0; gpr < (emu->audigy ? 0x200 : 0x100); gpr++) अणु
		set_bit(gpr, icode->gpr_valid);
		val = snd_emu10k1_ptr_पढ़ो(emu, emu->gpr_base + gpr, 0);
		अगर (put_user(val, (__user u32 *)&icode->gpr_map[gpr]))
			वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1_tram_poke(काष्ठा snd_emu10k1 *emu,
				 काष्ठा snd_emu10k1_fx8010_code *icode,
				 bool in_kernel)
अणु
	पूर्णांक tram;
	u32 addr, val;

	क्रम (tram = 0; tram < (emu->audigy ? 0x100 : 0xa0); tram++) अणु
		अगर (!test_bit(tram, icode->tram_valid))
			जारी;
		अगर (in_kernel) अणु
			val = icode->tram_data_map[tram];
			addr = icode->tram_addr_map[tram];
		पूर्ण अन्यथा अणु
			अगर (get_user(val, (__user __u32 *)&icode->tram_data_map[tram]) ||
			    get_user(addr, (__user __u32 *)&icode->tram_addr_map[tram]))
				वापस -EFAULT;
		पूर्ण
		snd_emu10k1_ptr_ग_लिखो(emu, TANKMEMDATAREGBASE + tram, 0, val);
		अगर (!emu->audigy) अणु
			snd_emu10k1_ptr_ग_लिखो(emu, TANKMEMADDRREGBASE + tram, 0, addr);
		पूर्ण अन्यथा अणु
			snd_emu10k1_ptr_ग_लिखो(emu, TANKMEMADDRREGBASE + tram, 0, addr << 12);
			snd_emu10k1_ptr_ग_लिखो(emu, A_TANKMEMCTLREGBASE + tram, 0, addr >> 20);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1_tram_peek(काष्ठा snd_emu10k1 *emu,
				 काष्ठा snd_emu10k1_fx8010_code *icode)
अणु
	पूर्णांक tram;
	u32 val, addr;

	स_रखो(icode->tram_valid, 0, माप(icode->tram_valid));
	क्रम (tram = 0; tram < (emu->audigy ? 0x100 : 0xa0); tram++) अणु
		set_bit(tram, icode->tram_valid);
		val = snd_emu10k1_ptr_पढ़ो(emu, TANKMEMDATAREGBASE + tram, 0);
		अगर (!emu->audigy) अणु
			addr = snd_emu10k1_ptr_पढ़ो(emu, TANKMEMADDRREGBASE + tram, 0);
		पूर्ण अन्यथा अणु
			addr = snd_emu10k1_ptr_पढ़ो(emu, TANKMEMADDRREGBASE + tram, 0) >> 12;
			addr |= snd_emu10k1_ptr_पढ़ो(emu, A_TANKMEMCTLREGBASE + tram, 0) << 20;
		पूर्ण
		अगर (put_user(val, (__user u32 *)&icode->tram_data_map[tram]) ||
		    put_user(addr, (__user u32 *)&icode->tram_addr_map[tram]))
			वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1_code_poke(काष्ठा snd_emu10k1 *emu,
				 काष्ठा snd_emu10k1_fx8010_code *icode,
				 bool in_kernel)
अणु
	u32 pc, lo, hi;

	क्रम (pc = 0; pc < (emu->audigy ? 2*1024 : 2*512); pc += 2) अणु
		अगर (!test_bit(pc / 2, icode->code_valid))
			जारी;
		अगर (in_kernel) अणु
			lo = icode->code[pc + 0];
			hi = icode->code[pc + 1];
		पूर्ण अन्यथा अणु
			अगर (get_user(lo, (__user u32 *)&icode->code[pc + 0]) ||
			    get_user(hi, (__user u32 *)&icode->code[pc + 1]))
				वापस -EFAULT;
		पूर्ण
		snd_emu10k1_efx_ग_लिखो(emu, pc + 0, lo);
		snd_emu10k1_efx_ग_लिखो(emu, pc + 1, hi);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1_code_peek(काष्ठा snd_emu10k1 *emu,
				 काष्ठा snd_emu10k1_fx8010_code *icode)
अणु
	u32 pc;

	स_रखो(icode->code_valid, 0, माप(icode->code_valid));
	क्रम (pc = 0; pc < (emu->audigy ? 2*1024 : 2*512); pc += 2) अणु
		set_bit(pc / 2, icode->code_valid);
		अगर (put_user(snd_emu10k1_efx_पढ़ो(emu, pc + 0),
			     (__user u32 *)&icode->code[pc + 0]))
			वापस -EFAULT;
		अगर (put_user(snd_emu10k1_efx_पढ़ो(emu, pc + 1),
			     (__user u32 *)&icode->code[pc + 1]))
			वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा snd_emu10k1_fx8010_ctl *
snd_emu10k1_look_क्रम_ctl(काष्ठा snd_emu10k1 *emu,
			 काष्ठा emu10k1_ctl_elem_id *_id)
अणु
	काष्ठा snd_ctl_elem_id *id = (काष्ठा snd_ctl_elem_id *)_id;
	काष्ठा snd_emu10k1_fx8010_ctl *ctl;
	काष्ठा snd_kcontrol *kcontrol;

	list_क्रम_each_entry(ctl, &emu->fx8010.gpr_ctl, list) अणु
		kcontrol = ctl->kcontrol;
		अगर (kcontrol->id.अगरace == id->अगरace &&
		    !म_भेद(kcontrol->id.name, id->name) &&
		    kcontrol->id.index == id->index)
			वापस ctl;
	पूर्ण
	वापस शून्य;
पूर्ण

#घोषणा MAX_TLV_SIZE	256

अटल अचिन्हित पूर्णांक *copy_tlv(स्थिर अचिन्हित पूर्णांक __user *_tlv, bool in_kernel)
अणु
	अचिन्हित पूर्णांक data[2];
	अचिन्हित पूर्णांक *tlv;

	अगर (!_tlv)
		वापस शून्य;
	अगर (in_kernel)
		स_नकल(data, (__क्रमce व्योम *)_tlv, माप(data));
	अन्यथा अगर (copy_from_user(data, _tlv, माप(data)))
		वापस शून्य;
	अगर (data[1] >= MAX_TLV_SIZE)
		वापस शून्य;
	tlv = kदो_स्मृति(data[1] + माप(data), GFP_KERNEL);
	अगर (!tlv)
		वापस शून्य;
	स_नकल(tlv, data, माप(data));
	अगर (in_kernel) अणु
		स_नकल(tlv + 2, (__क्रमce व्योम *)(_tlv + 2),  data[1]);
	पूर्ण अन्यथा अगर (copy_from_user(tlv + 2, _tlv + 2, data[1])) अणु
		kमुक्त(tlv);
		वापस शून्य;
	पूर्ण
	वापस tlv;
पूर्ण

अटल पूर्णांक copy_gctl(काष्ठा snd_emu10k1 *emu,
		     काष्ठा snd_emu10k1_fx8010_control_gpr *dst,
		     काष्ठा snd_emu10k1_fx8010_control_gpr *src,
		     पूर्णांक idx, bool in_kernel)
अणु
	काष्ठा snd_emu10k1_fx8010_control_gpr __user *_src;
	काष्ठा snd_emu10k1_fx8010_control_old_gpr *octl;
	काष्ठा snd_emu10k1_fx8010_control_old_gpr __user *_octl;

	_src = (काष्ठा snd_emu10k1_fx8010_control_gpr __user *)src;
	अगर (emu->support_tlv) अणु
		अगर (in_kernel)
			*dst = src[idx];
		अन्यथा अगर (copy_from_user(dst, &_src[idx], माप(*src)))
			वापस -EFAULT;
		वापस 0;
	पूर्ण

	octl = (काष्ठा snd_emu10k1_fx8010_control_old_gpr *)src;
	_octl = (काष्ठा snd_emu10k1_fx8010_control_old_gpr __user *)octl;
	अगर (in_kernel)
		स_नकल(dst, &octl[idx], माप(*octl));
	अन्यथा अगर (copy_from_user(dst, &_octl[idx], माप(*octl)))
		वापस -EFAULT;
	dst->tlv = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक copy_gctl_to_user(काष्ठा snd_emu10k1 *emu,
		     काष्ठा snd_emu10k1_fx8010_control_gpr *dst,
		     काष्ठा snd_emu10k1_fx8010_control_gpr *src,
		     पूर्णांक idx)
अणु
	काष्ठा snd_emu10k1_fx8010_control_gpr __user *_dst;
	काष्ठा snd_emu10k1_fx8010_control_old_gpr __user *octl;

	_dst = (काष्ठा snd_emu10k1_fx8010_control_gpr __user *)dst;
	अगर (emu->support_tlv)
		वापस copy_to_user(&_dst[idx], src, माप(*src));
	
	octl = (काष्ठा snd_emu10k1_fx8010_control_old_gpr __user *)dst;
	वापस copy_to_user(&octl[idx], src, माप(*octl));
पूर्ण

अटल पूर्णांक copy_ctl_elem_id(स्थिर काष्ठा emu10k1_ctl_elem_id *list, पूर्णांक i,
			    काष्ठा emu10k1_ctl_elem_id *ret, bool in_kernel)
अणु
	काष्ठा emu10k1_ctl_elem_id __user *_id =
		(काष्ठा emu10k1_ctl_elem_id __user *)&list[i];

	अगर (in_kernel)
		*ret = list[i];
	अन्यथा अगर (copy_from_user(ret, _id, माप(*ret)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1_verअगरy_controls(काष्ठा snd_emu10k1 *emu,
				       काष्ठा snd_emu10k1_fx8010_code *icode,
				       bool in_kernel)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा emu10k1_ctl_elem_id id;
	काष्ठा snd_emu10k1_fx8010_control_gpr *gctl;
	काष्ठा snd_ctl_elem_id *gctl_id;
	पूर्णांक err;
	
	क्रम (i = 0; i < icode->gpr_del_control_count; i++) अणु
		err = copy_ctl_elem_id(icode->gpr_del_controls, i, &id,
				       in_kernel);
		अगर (err < 0)
			वापस err;
		अगर (snd_emu10k1_look_क्रम_ctl(emu, &id) == शून्य)
			वापस -ENOENT;
	पूर्ण
	gctl = kदो_स्मृति(माप(*gctl), GFP_KERNEL);
	अगर (! gctl)
		वापस -ENOMEM;
	err = 0;
	क्रम (i = 0; i < icode->gpr_add_control_count; i++) अणु
		अगर (copy_gctl(emu, gctl, icode->gpr_add_controls, i,
			      in_kernel)) अणु
			err = -EFAULT;
			जाओ __error;
		पूर्ण
		अगर (snd_emu10k1_look_क्रम_ctl(emu, &gctl->id))
			जारी;
		gctl_id = (काष्ठा snd_ctl_elem_id *)&gctl->id;
		करोwn_पढ़ो(&emu->card->controls_rwsem);
		अगर (snd_ctl_find_id(emu->card, gctl_id)) अणु
			up_पढ़ो(&emu->card->controls_rwsem);
			err = -EEXIST;
			जाओ __error;
		पूर्ण
		up_पढ़ो(&emu->card->controls_rwsem);
		अगर (gctl_id->अगरace != SNDRV_CTL_ELEM_IFACE_MIXER &&
		    gctl_id->अगरace != SNDRV_CTL_ELEM_IFACE_PCM) अणु
			err = -EINVAL;
			जाओ __error;
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < icode->gpr_list_control_count; i++) अणु
	     	/* FIXME: we need to check the WRITE access */
		अगर (copy_gctl(emu, gctl, icode->gpr_list_controls, i,
			      in_kernel)) अणु
			err = -EFAULT;
			जाओ __error;
		पूर्ण
	पूर्ण
 __error:
	kमुक्त(gctl);
	वापस err;
पूर्ण

अटल व्योम snd_emu10k1_ctl_निजी_मुक्त(काष्ठा snd_kcontrol *kctl)
अणु
	काष्ठा snd_emu10k1_fx8010_ctl *ctl;
	
	ctl = (काष्ठा snd_emu10k1_fx8010_ctl *) kctl->निजी_value;
	kctl->निजी_value = 0;
	list_del(&ctl->list);
	kमुक्त(ctl);
	kमुक्त(kctl->tlv.p);
पूर्ण

अटल पूर्णांक snd_emu10k1_add_controls(काष्ठा snd_emu10k1 *emu,
				    काष्ठा snd_emu10k1_fx8010_code *icode,
				    bool in_kernel)
अणु
	अचिन्हित पूर्णांक i, j;
	काष्ठा snd_emu10k1_fx8010_control_gpr *gctl;
	काष्ठा snd_ctl_elem_id *gctl_id;
	काष्ठा snd_emu10k1_fx8010_ctl *ctl, *nctl;
	काष्ठा snd_kcontrol_new knew;
	काष्ठा snd_kcontrol *kctl;
	काष्ठा snd_ctl_elem_value *val;
	पूर्णांक err = 0;

	val = kदो_स्मृति(माप(*val), GFP_KERNEL);
	gctl = kदो_स्मृति(माप(*gctl), GFP_KERNEL);
	nctl = kदो_स्मृति(माप(*nctl), GFP_KERNEL);
	अगर (!val || !gctl || !nctl) अणु
		err = -ENOMEM;
		जाओ __error;
	पूर्ण

	क्रम (i = 0; i < icode->gpr_add_control_count; i++) अणु
		अगर (copy_gctl(emu, gctl, icode->gpr_add_controls, i,
			      in_kernel)) अणु
			err = -EFAULT;
			जाओ __error;
		पूर्ण
		gctl_id = (काष्ठा snd_ctl_elem_id *)&gctl->id;
		अगर (gctl_id->अगरace != SNDRV_CTL_ELEM_IFACE_MIXER &&
		    gctl_id->अगरace != SNDRV_CTL_ELEM_IFACE_PCM) अणु
			err = -EINVAL;
			जाओ __error;
		पूर्ण
		अगर (!*gctl_id->name) अणु
			err = -EINVAL;
			जाओ __error;
		पूर्ण
		ctl = snd_emu10k1_look_क्रम_ctl(emu, &gctl->id);
		स_रखो(&knew, 0, माप(knew));
		knew.अगरace = gctl_id->अगरace;
		knew.name = gctl_id->name;
		knew.index = gctl_id->index;
		knew.device = gctl_id->device;
		knew.subdevice = gctl_id->subdevice;
		knew.info = snd_emu10k1_gpr_ctl_info;
		knew.tlv.p = copy_tlv((स्थिर अचिन्हित पूर्णांक __user *)gctl->tlv, in_kernel);
		अगर (knew.tlv.p)
			knew.access = SNDRV_CTL_ELEM_ACCESS_READWRITE |
				SNDRV_CTL_ELEM_ACCESS_TLV_READ;
		knew.get = snd_emu10k1_gpr_ctl_get;
		knew.put = snd_emu10k1_gpr_ctl_put;
		स_रखो(nctl, 0, माप(*nctl));
		nctl->vcount = gctl->vcount;
		nctl->count = gctl->count;
		क्रम (j = 0; j < 32; j++) अणु
			nctl->gpr[j] = gctl->gpr[j];
			nctl->value[j] = ~gctl->value[j];	/* inverted, we want to ग_लिखो new value in gpr_ctl_put() */
			val->value.पूर्णांकeger.value[j] = gctl->value[j];
		पूर्ण
		nctl->min = gctl->min;
		nctl->max = gctl->max;
		nctl->translation = gctl->translation;
		अगर (ctl == शून्य) अणु
			ctl = kदो_स्मृति(माप(*ctl), GFP_KERNEL);
			अगर (ctl == शून्य) अणु
				err = -ENOMEM;
				kमुक्त(knew.tlv.p);
				जाओ __error;
			पूर्ण
			knew.निजी_value = (अचिन्हित दीर्घ)ctl;
			*ctl = *nctl;
			अगर ((err = snd_ctl_add(emu->card, kctl = snd_ctl_new1(&knew, emu))) < 0) अणु
				kमुक्त(ctl);
				kमुक्त(knew.tlv.p);
				जाओ __error;
			पूर्ण
			kctl->निजी_मुक्त = snd_emu10k1_ctl_निजी_मुक्त;
			ctl->kcontrol = kctl;
			list_add_tail(&ctl->list, &emu->fx8010.gpr_ctl);
		पूर्ण अन्यथा अणु
			/* overग_लिखो */
			nctl->list = ctl->list;
			nctl->kcontrol = ctl->kcontrol;
			*ctl = *nctl;
			snd_ctl_notअगरy(emu->card, SNDRV_CTL_EVENT_MASK_VALUE |
			                          SNDRV_CTL_EVENT_MASK_INFO, &ctl->kcontrol->id);
		पूर्ण
		snd_emu10k1_gpr_ctl_put(ctl->kcontrol, val);
	पूर्ण
      __error:
	kमुक्त(nctl);
	kमुक्त(gctl);
	kमुक्त(val);
	वापस err;
पूर्ण

अटल पूर्णांक snd_emu10k1_del_controls(काष्ठा snd_emu10k1 *emu,
				    काष्ठा snd_emu10k1_fx8010_code *icode,
				    bool in_kernel)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा emu10k1_ctl_elem_id id;
	काष्ठा snd_emu10k1_fx8010_ctl *ctl;
	काष्ठा snd_card *card = emu->card;
	पूर्णांक err;
	
	क्रम (i = 0; i < icode->gpr_del_control_count; i++) अणु
		err = copy_ctl_elem_id(icode->gpr_del_controls, i, &id,
				       in_kernel);
		अगर (err < 0)
			वापस err;
		करोwn_ग_लिखो(&card->controls_rwsem);
		ctl = snd_emu10k1_look_क्रम_ctl(emu, &id);
		अगर (ctl)
			snd_ctl_हटाओ(card, ctl->kcontrol);
		up_ग_लिखो(&card->controls_rwsem);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1_list_controls(काष्ठा snd_emu10k1 *emu,
				     काष्ठा snd_emu10k1_fx8010_code *icode)
अणु
	अचिन्हित पूर्णांक i = 0, j;
	अचिन्हित पूर्णांक total = 0;
	काष्ठा snd_emu10k1_fx8010_control_gpr *gctl;
	काष्ठा snd_emu10k1_fx8010_ctl *ctl;
	काष्ठा snd_ctl_elem_id *id;

	gctl = kदो_स्मृति(माप(*gctl), GFP_KERNEL);
	अगर (! gctl)
		वापस -ENOMEM;

	list_क्रम_each_entry(ctl, &emu->fx8010.gpr_ctl, list) अणु
		total++;
		अगर (icode->gpr_list_controls &&
		    i < icode->gpr_list_control_count) अणु
			स_रखो(gctl, 0, माप(*gctl));
			id = &ctl->kcontrol->id;
			gctl->id.अगरace = (__क्रमce पूर्णांक)id->अगरace;
			strscpy(gctl->id.name, id->name, माप(gctl->id.name));
			gctl->id.index = id->index;
			gctl->id.device = id->device;
			gctl->id.subdevice = id->subdevice;
			gctl->vcount = ctl->vcount;
			gctl->count = ctl->count;
			क्रम (j = 0; j < 32; j++) अणु
				gctl->gpr[j] = ctl->gpr[j];
				gctl->value[j] = ctl->value[j];
			पूर्ण
			gctl->min = ctl->min;
			gctl->max = ctl->max;
			gctl->translation = ctl->translation;
			अगर (copy_gctl_to_user(emu, icode->gpr_list_controls,
					      gctl, i)) अणु
				kमुक्त(gctl);
				वापस -EFAULT;
			पूर्ण
			i++;
		पूर्ण
	पूर्ण
	icode->gpr_list_control_total = total;
	kमुक्त(gctl);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1_icode_poke(काष्ठा snd_emu10k1 *emu,
				  काष्ठा snd_emu10k1_fx8010_code *icode,
				  bool in_kernel)
अणु
	पूर्णांक err = 0;

	mutex_lock(&emu->fx8010.lock);
	err = snd_emu10k1_verअगरy_controls(emu, icode, in_kernel);
	अगर (err < 0)
		जाओ __error;
	strscpy(emu->fx8010.name, icode->name, माप(emu->fx8010.name));
	/* stop FX processor - this may be dangerous, but it's better to miss
	   some samples than generate wrong ones - [jk] */
	अगर (emu->audigy)
		snd_emu10k1_ptr_ग_लिखो(emu, A_DBG, 0, emu->fx8010.dbg | A_DBG_SINGLE_STEP);
	अन्यथा
		snd_emu10k1_ptr_ग_लिखो(emu, DBG, 0, emu->fx8010.dbg | EMU10K1_DBG_SINGLE_STEP);
	/* ok, करो the मुख्य job */
	err = snd_emu10k1_del_controls(emu, icode, in_kernel);
	अगर (err < 0)
		जाओ __error;
	err = snd_emu10k1_gpr_poke(emu, icode, in_kernel);
	अगर (err < 0)
		जाओ __error;
	err = snd_emu10k1_tram_poke(emu, icode, in_kernel);
	अगर (err < 0)
		जाओ __error;
	err = snd_emu10k1_code_poke(emu, icode, in_kernel);
	अगर (err < 0)
		जाओ __error;
	err = snd_emu10k1_add_controls(emu, icode, in_kernel);
	अगर (err < 0)
		जाओ __error;
	/* start FX processor when the DSP code is updated */
	अगर (emu->audigy)
		snd_emu10k1_ptr_ग_लिखो(emu, A_DBG, 0, emu->fx8010.dbg);
	अन्यथा
		snd_emu10k1_ptr_ग_लिखो(emu, DBG, 0, emu->fx8010.dbg);
      __error:
	mutex_unlock(&emu->fx8010.lock);
	वापस err;
पूर्ण

अटल पूर्णांक snd_emu10k1_icode_peek(काष्ठा snd_emu10k1 *emu,
				  काष्ठा snd_emu10k1_fx8010_code *icode)
अणु
	पूर्णांक err;

	mutex_lock(&emu->fx8010.lock);
	strscpy(icode->name, emu->fx8010.name, माप(icode->name));
	/* ok, करो the मुख्य job */
	err = snd_emu10k1_gpr_peek(emu, icode);
	अगर (err >= 0)
		err = snd_emu10k1_tram_peek(emu, icode);
	अगर (err >= 0)
		err = snd_emu10k1_code_peek(emu, icode);
	अगर (err >= 0)
		err = snd_emu10k1_list_controls(emu, icode);
	mutex_unlock(&emu->fx8010.lock);
	वापस err;
पूर्ण

अटल पूर्णांक snd_emu10k1_ipcm_poke(काष्ठा snd_emu10k1 *emu,
				 काष्ठा snd_emu10k1_fx8010_pcm_rec *ipcm)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err = 0;
	काष्ठा snd_emu10k1_fx8010_pcm *pcm;

	अगर (ipcm->substream >= EMU10K1_FX8010_PCM_COUNT)
		वापस -EINVAL;
	ipcm->substream = array_index_nospec(ipcm->substream,
					     EMU10K1_FX8010_PCM_COUNT);
	अगर (ipcm->channels > 32)
		वापस -EINVAL;
	pcm = &emu->fx8010.pcm[ipcm->substream];
	mutex_lock(&emu->fx8010.lock);
	spin_lock_irq(&emu->reg_lock);
	अगर (pcm->खोलोed) अणु
		err = -EBUSY;
		जाओ __error;
	पूर्ण
	अगर (ipcm->channels == 0) अणु	/* हटाओ */
		pcm->valid = 0;
	पूर्ण अन्यथा अणु
		/* FIXME: we need to add universal code to the PCM transfer routine */
		अगर (ipcm->channels != 2) अणु
			err = -EINVAL;
			जाओ __error;
		पूर्ण
		pcm->valid = 1;
		pcm->खोलोed = 0;
		pcm->channels = ipcm->channels;
		pcm->tram_start = ipcm->tram_start;
		pcm->buffer_size = ipcm->buffer_size;
		pcm->gpr_size = ipcm->gpr_size;
		pcm->gpr_count = ipcm->gpr_count;
		pcm->gpr_पंचांगpcount = ipcm->gpr_पंचांगpcount;
		pcm->gpr_ptr = ipcm->gpr_ptr;
		pcm->gpr_trigger = ipcm->gpr_trigger;
		pcm->gpr_running = ipcm->gpr_running;
		क्रम (i = 0; i < pcm->channels; i++)
			pcm->etram[i] = ipcm->etram[i];
	पूर्ण
      __error:
	spin_unlock_irq(&emu->reg_lock);
	mutex_unlock(&emu->fx8010.lock);
	वापस err;
पूर्ण

अटल पूर्णांक snd_emu10k1_ipcm_peek(काष्ठा snd_emu10k1 *emu,
				 काष्ठा snd_emu10k1_fx8010_pcm_rec *ipcm)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err = 0;
	काष्ठा snd_emu10k1_fx8010_pcm *pcm;

	अगर (ipcm->substream >= EMU10K1_FX8010_PCM_COUNT)
		वापस -EINVAL;
	ipcm->substream = array_index_nospec(ipcm->substream,
					     EMU10K1_FX8010_PCM_COUNT);
	pcm = &emu->fx8010.pcm[ipcm->substream];
	mutex_lock(&emu->fx8010.lock);
	spin_lock_irq(&emu->reg_lock);
	ipcm->channels = pcm->channels;
	ipcm->tram_start = pcm->tram_start;
	ipcm->buffer_size = pcm->buffer_size;
	ipcm->gpr_size = pcm->gpr_size;
	ipcm->gpr_ptr = pcm->gpr_ptr;
	ipcm->gpr_count = pcm->gpr_count;
	ipcm->gpr_पंचांगpcount = pcm->gpr_पंचांगpcount;
	ipcm->gpr_trigger = pcm->gpr_trigger;
	ipcm->gpr_running = pcm->gpr_running;
	क्रम (i = 0; i < pcm->channels; i++)
		ipcm->etram[i] = pcm->etram[i];
	ipcm->res1 = ipcm->res2 = 0;
	ipcm->pad = 0;
	spin_unlock_irq(&emu->reg_lock);
	mutex_unlock(&emu->fx8010.lock);
	वापस err;
पूर्ण

#घोषणा SND_EMU10K1_GPR_CONTROLS	44
#घोषणा SND_EMU10K1_INPUTS		12
#घोषणा SND_EMU10K1_PLAYBACK_CHANNELS	8
#घोषणा SND_EMU10K1_CAPTURE_CHANNELS	4

अटल व्योम
snd_emu10k1_init_mono_control(काष्ठा snd_emu10k1_fx8010_control_gpr *ctl,
			      स्थिर अक्षर *name, पूर्णांक gpr, पूर्णांक defval)
अणु
	ctl->id.अगरace = (__क्रमce पूर्णांक)SNDRV_CTL_ELEM_IFACE_MIXER;
	म_नकल(ctl->id.name, name);
	ctl->vcount = ctl->count = 1;
	ctl->gpr[0] = gpr + 0; ctl->value[0] = defval;
	अगर (high_res_gpr_volume) अणु
		ctl->min = 0;
		ctl->max = 0x7fffffff;
		ctl->tlv = snd_emu10k1_db_linear;
		ctl->translation = EMU10K1_GPR_TRANSLATION_NONE;
	पूर्ण अन्यथा अणु
		ctl->min = 0;
		ctl->max = 100;
		ctl->tlv = snd_emu10k1_db_scale1;
		ctl->translation = EMU10K1_GPR_TRANSLATION_TABLE100;
	पूर्ण
पूर्ण

अटल व्योम
snd_emu10k1_init_stereo_control(काष्ठा snd_emu10k1_fx8010_control_gpr *ctl,
				स्थिर अक्षर *name, पूर्णांक gpr, पूर्णांक defval)
अणु
	ctl->id.अगरace = (__क्रमce पूर्णांक)SNDRV_CTL_ELEM_IFACE_MIXER;
	म_नकल(ctl->id.name, name);
	ctl->vcount = ctl->count = 2;
	ctl->gpr[0] = gpr + 0; ctl->value[0] = defval;
	ctl->gpr[1] = gpr + 1; ctl->value[1] = defval;
	अगर (high_res_gpr_volume) अणु
		ctl->min = 0;
		ctl->max = 0x7fffffff;
		ctl->tlv = snd_emu10k1_db_linear;
		ctl->translation = EMU10K1_GPR_TRANSLATION_NONE;
	पूर्ण अन्यथा अणु
		ctl->min = 0;
		ctl->max = 100;
		ctl->tlv = snd_emu10k1_db_scale1;
		ctl->translation = EMU10K1_GPR_TRANSLATION_TABLE100;
	पूर्ण
पूर्ण

अटल व्योम
snd_emu10k1_init_mono_onoff_control(काष्ठा snd_emu10k1_fx8010_control_gpr *ctl,
				    स्थिर अक्षर *name, पूर्णांक gpr, पूर्णांक defval)
अणु
	ctl->id.अगरace = (__क्रमce पूर्णांक)SNDRV_CTL_ELEM_IFACE_MIXER;
	म_नकल(ctl->id.name, name);
	ctl->vcount = ctl->count = 1;
	ctl->gpr[0] = gpr + 0; ctl->value[0] = defval;
	ctl->min = 0;
	ctl->max = 1;
	ctl->translation = EMU10K1_GPR_TRANSLATION_ONOFF;
पूर्ण

अटल व्योम
snd_emu10k1_init_stereo_onoff_control(काष्ठा snd_emu10k1_fx8010_control_gpr *ctl,
				      स्थिर अक्षर *name, पूर्णांक gpr, पूर्णांक defval)
अणु
	ctl->id.अगरace = (__क्रमce पूर्णांक)SNDRV_CTL_ELEM_IFACE_MIXER;
	म_नकल(ctl->id.name, name);
	ctl->vcount = ctl->count = 2;
	ctl->gpr[0] = gpr + 0; ctl->value[0] = defval;
	ctl->gpr[1] = gpr + 1; ctl->value[1] = defval;
	ctl->min = 0;
	ctl->max = 1;
	ctl->translation = EMU10K1_GPR_TRANSLATION_ONOFF;
पूर्ण

/*
 * Used क्रम emu1010 - conversion from 32-bit capture inमाला_दो from HANA
 * to 2 x 16-bit रेजिस्टरs in audigy - their values are पढ़ो via DMA.
 * Conversion is perक्रमmed by Audigy DSP inकाष्ठाions of FX8010.
 */
अटल पूर्णांक snd_emu10k1_audigy_dsp_convert_32_to_2x16(
				काष्ठा snd_emu10k1_fx8010_code *icode,
				u32 *ptr, पूर्णांक पंचांगp, पूर्णांक bit_shअगरter16,
				पूर्णांक reg_in, पूर्णांक reg_out)
अणु
	A_OP(icode, ptr, iACC3, A_GPR(पंचांगp + 1), reg_in, A_C_00000000, A_C_00000000);
	A_OP(icode, ptr, iANDXOR, A_GPR(पंचांगp), A_GPR(पंचांगp + 1), A_GPR(bit_shअगरter16 - 1), A_C_00000000);
	A_OP(icode, ptr, iTSTNEG, A_GPR(पंचांगp + 2), A_GPR(पंचांगp), A_C_80000000, A_GPR(bit_shअगरter16 - 2));
	A_OP(icode, ptr, iANDXOR, A_GPR(पंचांगp + 2), A_GPR(पंचांगp + 2), A_C_80000000, A_C_00000000);
	A_OP(icode, ptr, iANDXOR, A_GPR(पंचांगp), A_GPR(पंचांगp), A_GPR(bit_shअगरter16 - 3), A_C_00000000);
	A_OP(icode, ptr, iMACINT0, A_GPR(पंचांगp), A_C_00000000, A_GPR(पंचांगp), A_C_00010000);
	A_OP(icode, ptr, iANDXOR, reg_out, A_GPR(पंचांगp), A_C_ffffffff, A_GPR(पंचांगp + 2));
	A_OP(icode, ptr, iACC3, reg_out + 1, A_GPR(पंचांगp + 1), A_C_00000000, A_C_00000000);
	वापस 1;
पूर्ण

/*
 * initial DSP configuration क्रम Audigy
 */

अटल पूर्णांक _snd_emu10k1_audigy_init_efx(काष्ठा snd_emu10k1 *emu)
अणु
	पूर्णांक err, i, z, gpr, nctl;
	पूर्णांक bit_shअगरter16;
	स्थिर पूर्णांक playback = 10;
	स्थिर पूर्णांक capture = playback + (SND_EMU10K1_PLAYBACK_CHANNELS * 2); /* we reserve 10 voices */
	स्थिर पूर्णांक stereo_mix = capture + 2;
	स्थिर पूर्णांक पंचांगp = 0x88;
	u32 ptr;
	काष्ठा snd_emu10k1_fx8010_code *icode = शून्य;
	काष्ठा snd_emu10k1_fx8010_control_gpr *controls = शून्य, *ctl;
	u32 *gpr_map;

	err = -ENOMEM;
	icode = kzalloc(माप(*icode), GFP_KERNEL);
	अगर (!icode)
		वापस err;

	icode->gpr_map = kसुस्मृति(512 + 256 + 256 + 2 * 1024,
				 माप(u_पूर्णांक32_t), GFP_KERNEL);
	अगर (!icode->gpr_map)
		जाओ __err_gpr;
	controls = kसुस्मृति(SND_EMU10K1_GPR_CONTROLS,
			   माप(*controls), GFP_KERNEL);
	अगर (!controls)
		जाओ __err_ctrls;

	gpr_map = icode->gpr_map;

	icode->tram_data_map = icode->gpr_map + 512;
	icode->tram_addr_map = icode->tram_data_map + 256;
	icode->code = icode->tram_addr_map + 256;

	/* clear मुक्त GPRs */
	क्रम (i = 0; i < 512; i++)
		set_bit(i, icode->gpr_valid);
		
	/* clear TRAM data & address lines */
	क्रम (i = 0; i < 256; i++)
		set_bit(i, icode->tram_valid);

	म_नकल(icode->name, "Audigy DSP code for ALSA");
	ptr = 0;
	nctl = 0;
	gpr = stereo_mix + 10;
	gpr_map[gpr++] = 0x00007fff;
	gpr_map[gpr++] = 0x00008000;
	gpr_map[gpr++] = 0x0000ffff;
	bit_shअगरter16 = gpr;

	/* stop FX processor */
	snd_emu10k1_ptr_ग_लिखो(emu, A_DBG, 0, (emu->fx8010.dbg = 0) | A_DBG_SINGLE_STEP);

#अगर 1
	/* PCM front Playback Volume (independent from stereo mix)
	 * playback = 0 + ( gpr * FXBUS_PCM_LEFT_FRONT >> 31)
	 * where gpr contains attenuation from corresponding mixer control
	 * (snd_emu10k1_init_stereo_control)
	 */
	A_OP(icode, &ptr, iMAC0, A_GPR(playback), A_C_00000000, A_GPR(gpr), A_FXBUS(FXBUS_PCM_LEFT_FRONT));
	A_OP(icode, &ptr, iMAC0, A_GPR(playback+1), A_C_00000000, A_GPR(gpr+1), A_FXBUS(FXBUS_PCM_RIGHT_FRONT));
	snd_emu10k1_init_stereo_control(&controls[nctl++], "PCM Front Playback Volume", gpr, 100);
	gpr += 2;

	/* PCM Surround Playback (independent from stereo mix) */
	A_OP(icode, &ptr, iMAC0, A_GPR(playback+2), A_C_00000000, A_GPR(gpr), A_FXBUS(FXBUS_PCM_LEFT_REAR));
	A_OP(icode, &ptr, iMAC0, A_GPR(playback+3), A_C_00000000, A_GPR(gpr+1), A_FXBUS(FXBUS_PCM_RIGHT_REAR));
	snd_emu10k1_init_stereo_control(&controls[nctl++], "PCM Surround Playback Volume", gpr, 100);
	gpr += 2;
	
	/* PCM Side Playback (independent from stereo mix) */
	अगर (emu->card_capabilities->spk71) अणु
		A_OP(icode, &ptr, iMAC0, A_GPR(playback+6), A_C_00000000, A_GPR(gpr), A_FXBUS(FXBUS_PCM_LEFT_SIDE));
		A_OP(icode, &ptr, iMAC0, A_GPR(playback+7), A_C_00000000, A_GPR(gpr+1), A_FXBUS(FXBUS_PCM_RIGHT_SIDE));
		snd_emu10k1_init_stereo_control(&controls[nctl++], "PCM Side Playback Volume", gpr, 100);
		gpr += 2;
	पूर्ण

	/* PCM Center Playback (independent from stereo mix) */
	A_OP(icode, &ptr, iMAC0, A_GPR(playback+4), A_C_00000000, A_GPR(gpr), A_FXBUS(FXBUS_PCM_CENTER));
	snd_emu10k1_init_mono_control(&controls[nctl++], "PCM Center Playback Volume", gpr, 100);
	gpr++;

	/* PCM LFE Playback (independent from stereo mix) */
	A_OP(icode, &ptr, iMAC0, A_GPR(playback+5), A_C_00000000, A_GPR(gpr), A_FXBUS(FXBUS_PCM_LFE));
	snd_emu10k1_init_mono_control(&controls[nctl++], "PCM LFE Playback Volume", gpr, 100);
	gpr++;
	
	/*
	 * Stereo Mix
	 */
	/* Wave (PCM) Playback Volume (will be नामd later) */
	A_OP(icode, &ptr, iMAC0, A_GPR(stereo_mix), A_C_00000000, A_GPR(gpr), A_FXBUS(FXBUS_PCM_LEFT));
	A_OP(icode, &ptr, iMAC0, A_GPR(stereo_mix+1), A_C_00000000, A_GPR(gpr+1), A_FXBUS(FXBUS_PCM_RIGHT));
	snd_emu10k1_init_stereo_control(&controls[nctl++], "Wave Playback Volume", gpr, 100);
	gpr += 2;

	/* Synth Playback */
	A_OP(icode, &ptr, iMAC0, A_GPR(stereo_mix+0), A_GPR(stereo_mix+0), A_GPR(gpr), A_FXBUS(FXBUS_MIDI_LEFT));
	A_OP(icode, &ptr, iMAC0, A_GPR(stereo_mix+1), A_GPR(stereo_mix+1), A_GPR(gpr+1), A_FXBUS(FXBUS_MIDI_RIGHT));
	snd_emu10k1_init_stereo_control(&controls[nctl++], "Synth Playback Volume", gpr, 100);
	gpr += 2;

	/* Wave (PCM) Capture */
	A_OP(icode, &ptr, iMAC0, A_GPR(capture+0), A_C_00000000, A_GPR(gpr), A_FXBUS(FXBUS_PCM_LEFT));
	A_OP(icode, &ptr, iMAC0, A_GPR(capture+1), A_C_00000000, A_GPR(gpr+1), A_FXBUS(FXBUS_PCM_RIGHT));
	snd_emu10k1_init_stereo_control(&controls[nctl++], "PCM Capture Volume", gpr, 0);
	gpr += 2;

	/* Synth Capture */
	A_OP(icode, &ptr, iMAC0, A_GPR(capture+0), A_GPR(capture+0), A_GPR(gpr), A_FXBUS(FXBUS_MIDI_LEFT));
	A_OP(icode, &ptr, iMAC0, A_GPR(capture+1), A_GPR(capture+1), A_GPR(gpr+1), A_FXBUS(FXBUS_MIDI_RIGHT));
	snd_emu10k1_init_stereo_control(&controls[nctl++], "Synth Capture Volume", gpr, 0);
	gpr += 2;
      
	/*
	 * inमाला_दो
	 */
#घोषणा A_ADD_VOLUME_IN(var,vol,input) \
A_OP(icode, &ptr, iMAC0, A_GPR(var), A_GPR(var), A_GPR(vol), A_EXTIN(input))

	/* emu1212 DSP 0 and DSP 1 Capture */
	अगर (emu->card_capabilities->emu_model) अणु
		अगर (emu->card_capabilities->ca0108_chip) अणु
			/* Note:JCD:No दीर्घer bit shअगरt lower 16bits to upper 16bits of 32bit value. */
			A_OP(icode, &ptr, iMACINT0, A_GPR(पंचांगp), A_C_00000000, A3_EMU32IN(0x0), A_C_00000001);
			A_OP(icode, &ptr, iMAC0, A_GPR(capture+0), A_GPR(capture+0), A_GPR(gpr), A_GPR(पंचांगp));
			A_OP(icode, &ptr, iMACINT0, A_GPR(पंचांगp), A_C_00000000, A3_EMU32IN(0x1), A_C_00000001);
			A_OP(icode, &ptr, iMAC0, A_GPR(capture+1), A_GPR(capture+1), A_GPR(gpr), A_GPR(पंचांगp));
		पूर्ण अन्यथा अणु
			A_OP(icode, &ptr, iMAC0, A_GPR(capture+0), A_GPR(capture+0), A_GPR(gpr), A_P16VIN(0x0));
			A_OP(icode, &ptr, iMAC0, A_GPR(capture+1), A_GPR(capture+1), A_GPR(gpr+1), A_P16VIN(0x1));
		पूर्ण
		snd_emu10k1_init_stereo_control(&controls[nctl++], "EMU Capture Volume", gpr, 0);
		gpr += 2;
	पूर्ण
	/* AC'97 Playback Volume - used only क्रम mic (नामd later) */
	A_ADD_VOLUME_IN(stereo_mix, gpr, A_EXTIN_AC97_L);
	A_ADD_VOLUME_IN(stereo_mix+1, gpr+1, A_EXTIN_AC97_R);
	snd_emu10k1_init_stereo_control(&controls[nctl++], "AMic Playback Volume", gpr, 0);
	gpr += 2;
	/* AC'97 Capture Volume - used only क्रम mic */
	A_ADD_VOLUME_IN(capture, gpr, A_EXTIN_AC97_L);
	A_ADD_VOLUME_IN(capture+1, gpr+1, A_EXTIN_AC97_R);
	snd_emu10k1_init_stereo_control(&controls[nctl++], "Mic Capture Volume", gpr, 0);
	gpr += 2;

	/* mic capture buffer */	
	A_OP(icode, &ptr, iINTERP, A_EXTOUT(A_EXTOUT_MIC_CAP), A_EXTIN(A_EXTIN_AC97_L), 0xcd, A_EXTIN(A_EXTIN_AC97_R));

	/* Audigy CD Playback Volume */
	A_ADD_VOLUME_IN(stereo_mix, gpr, A_EXTIN_SPDIF_CD_L);
	A_ADD_VOLUME_IN(stereo_mix+1, gpr+1, A_EXTIN_SPDIF_CD_R);
	snd_emu10k1_init_stereo_control(&controls[nctl++],
					emu->card_capabilities->ac97_chip ? "Audigy CD Playback Volume" : "CD Playback Volume",
					gpr, 0);
	gpr += 2;
	/* Audigy CD Capture Volume */
	A_ADD_VOLUME_IN(capture, gpr, A_EXTIN_SPDIF_CD_L);
	A_ADD_VOLUME_IN(capture+1, gpr+1, A_EXTIN_SPDIF_CD_R);
	snd_emu10k1_init_stereo_control(&controls[nctl++],
					emu->card_capabilities->ac97_chip ? "Audigy CD Capture Volume" : "CD Capture Volume",
					gpr, 0);
	gpr += 2;

 	/* Optical SPDIF Playback Volume */
	A_ADD_VOLUME_IN(stereo_mix, gpr, A_EXTIN_OPT_SPDIF_L);
	A_ADD_VOLUME_IN(stereo_mix+1, gpr+1, A_EXTIN_OPT_SPDIF_R);
	snd_emu10k1_init_stereo_control(&controls[nctl++], SNDRV_CTL_NAME_IEC958("Optical ",PLAYBACK,VOLUME), gpr, 0);
	gpr += 2;
	/* Optical SPDIF Capture Volume */
	A_ADD_VOLUME_IN(capture, gpr, A_EXTIN_OPT_SPDIF_L);
	A_ADD_VOLUME_IN(capture+1, gpr+1, A_EXTIN_OPT_SPDIF_R);
	snd_emu10k1_init_stereo_control(&controls[nctl++], SNDRV_CTL_NAME_IEC958("Optical ",CAPTURE,VOLUME), gpr, 0);
	gpr += 2;

	/* Line2 Playback Volume */
	A_ADD_VOLUME_IN(stereo_mix, gpr, A_EXTIN_LINE2_L);
	A_ADD_VOLUME_IN(stereo_mix+1, gpr+1, A_EXTIN_LINE2_R);
	snd_emu10k1_init_stereo_control(&controls[nctl++],
					emu->card_capabilities->ac97_chip ? "Line2 Playback Volume" : "Line Playback Volume",
					gpr, 0);
	gpr += 2;
	/* Line2 Capture Volume */
	A_ADD_VOLUME_IN(capture, gpr, A_EXTIN_LINE2_L);
	A_ADD_VOLUME_IN(capture+1, gpr+1, A_EXTIN_LINE2_R);
	snd_emu10k1_init_stereo_control(&controls[nctl++],
					emu->card_capabilities->ac97_chip ? "Line2 Capture Volume" : "Line Capture Volume",
					gpr, 0);
	gpr += 2;
        
	/* Philips ADC Playback Volume */
	A_ADD_VOLUME_IN(stereo_mix, gpr, A_EXTIN_ADC_L);
	A_ADD_VOLUME_IN(stereo_mix+1, gpr+1, A_EXTIN_ADC_R);
	snd_emu10k1_init_stereo_control(&controls[nctl++], "Analog Mix Playback Volume", gpr, 0);
	gpr += 2;
	/* Philips ADC Capture Volume */
	A_ADD_VOLUME_IN(capture, gpr, A_EXTIN_ADC_L);
	A_ADD_VOLUME_IN(capture+1, gpr+1, A_EXTIN_ADC_R);
	snd_emu10k1_init_stereo_control(&controls[nctl++], "Analog Mix Capture Volume", gpr, 0);
	gpr += 2;

	/* Aux2 Playback Volume */
	A_ADD_VOLUME_IN(stereo_mix, gpr, A_EXTIN_AUX2_L);
	A_ADD_VOLUME_IN(stereo_mix+1, gpr+1, A_EXTIN_AUX2_R);
	snd_emu10k1_init_stereo_control(&controls[nctl++],
					emu->card_capabilities->ac97_chip ? "Aux2 Playback Volume" : "Aux Playback Volume",
					gpr, 0);
	gpr += 2;
	/* Aux2 Capture Volume */
	A_ADD_VOLUME_IN(capture, gpr, A_EXTIN_AUX2_L);
	A_ADD_VOLUME_IN(capture+1, gpr+1, A_EXTIN_AUX2_R);
	snd_emu10k1_init_stereo_control(&controls[nctl++],
					emu->card_capabilities->ac97_chip ? "Aux2 Capture Volume" : "Aux Capture Volume",
					gpr, 0);
	gpr += 2;
	
	/* Stereo Mix Front Playback Volume */
	A_OP(icode, &ptr, iMAC0, A_GPR(playback), A_GPR(playback), A_GPR(gpr), A_GPR(stereo_mix));
	A_OP(icode, &ptr, iMAC0, A_GPR(playback+1), A_GPR(playback+1), A_GPR(gpr+1), A_GPR(stereo_mix+1));
	snd_emu10k1_init_stereo_control(&controls[nctl++], "Front Playback Volume", gpr, 100);
	gpr += 2;
	
	/* Stereo Mix Surround Playback */
	A_OP(icode, &ptr, iMAC0, A_GPR(playback+2), A_GPR(playback+2), A_GPR(gpr), A_GPR(stereo_mix));
	A_OP(icode, &ptr, iMAC0, A_GPR(playback+3), A_GPR(playback+3), A_GPR(gpr+1), A_GPR(stereo_mix+1));
	snd_emu10k1_init_stereo_control(&controls[nctl++], "Surround Playback Volume", gpr, 0);
	gpr += 2;

	/* Stereo Mix Center Playback */
	/* Center = sub = Left/2 + Right/2 */
	A_OP(icode, &ptr, iINTERP, A_GPR(पंचांगp), A_GPR(stereo_mix), 0xcd, A_GPR(stereo_mix+1));
	A_OP(icode, &ptr, iMAC0, A_GPR(playback+4), A_GPR(playback+4), A_GPR(gpr), A_GPR(पंचांगp));
	snd_emu10k1_init_mono_control(&controls[nctl++], "Center Playback Volume", gpr, 0);
	gpr++;

	/* Stereo Mix LFE Playback */
	A_OP(icode, &ptr, iMAC0, A_GPR(playback+5), A_GPR(playback+5), A_GPR(gpr), A_GPR(पंचांगp));
	snd_emu10k1_init_mono_control(&controls[nctl++], "LFE Playback Volume", gpr, 0);
	gpr++;
	
	अगर (emu->card_capabilities->spk71) अणु
		/* Stereo Mix Side Playback */
		A_OP(icode, &ptr, iMAC0, A_GPR(playback+6), A_GPR(playback+6), A_GPR(gpr), A_GPR(stereo_mix));
		A_OP(icode, &ptr, iMAC0, A_GPR(playback+7), A_GPR(playback+7), A_GPR(gpr+1), A_GPR(stereo_mix+1));
		snd_emu10k1_init_stereo_control(&controls[nctl++], "Side Playback Volume", gpr, 0);
		gpr += 2;
	पूर्ण

	/*
	 * outमाला_दो
	 */
#घोषणा A_PUT_OUTPUT(out,src) A_OP(icode, &ptr, iACC3, A_EXTOUT(out), A_C_00000000, A_C_00000000, A_GPR(src))
#घोषणा A_PUT_STEREO_OUTPUT(out1,out2,src) \
	अणुA_PUT_OUTPUT(out1,src); A_PUT_OUTPUT(out2,src+1);पूर्ण

#घोषणा _A_SWITCH(icode, ptr, dst, src, sw) \
	A_OP((icode), ptr, iMACINT0, dst, A_C_00000000, src, sw);
#घोषणा A_SWITCH(icode, ptr, dst, src, sw) \
		_A_SWITCH(icode, ptr, A_GPR(dst), A_GPR(src), A_GPR(sw))
#घोषणा _A_SWITCH_NEG(icode, ptr, dst, src) \
	A_OP((icode), ptr, iANDXOR, dst, src, A_C_00000001, A_C_00000001);
#घोषणा A_SWITCH_NEG(icode, ptr, dst, src) \
		_A_SWITCH_NEG(icode, ptr, A_GPR(dst), A_GPR(src))


	/*
	 *  Process tone control
	 */
	A_OP(icode, &ptr, iACC3, A_GPR(playback + SND_EMU10K1_PLAYBACK_CHANNELS + 0), A_GPR(playback + 0), A_C_00000000, A_C_00000000); /* left */
	A_OP(icode, &ptr, iACC3, A_GPR(playback + SND_EMU10K1_PLAYBACK_CHANNELS + 1), A_GPR(playback + 1), A_C_00000000, A_C_00000000); /* right */
	A_OP(icode, &ptr, iACC3, A_GPR(playback + SND_EMU10K1_PLAYBACK_CHANNELS + 2), A_GPR(playback + 2), A_C_00000000, A_C_00000000); /* rear left */
	A_OP(icode, &ptr, iACC3, A_GPR(playback + SND_EMU10K1_PLAYBACK_CHANNELS + 3), A_GPR(playback + 3), A_C_00000000, A_C_00000000); /* rear right */
	A_OP(icode, &ptr, iACC3, A_GPR(playback + SND_EMU10K1_PLAYBACK_CHANNELS + 4), A_GPR(playback + 4), A_C_00000000, A_C_00000000); /* center */
	A_OP(icode, &ptr, iACC3, A_GPR(playback + SND_EMU10K1_PLAYBACK_CHANNELS + 5), A_GPR(playback + 5), A_C_00000000, A_C_00000000); /* LFE */
	अगर (emu->card_capabilities->spk71) अणु
		A_OP(icode, &ptr, iACC3, A_GPR(playback + SND_EMU10K1_PLAYBACK_CHANNELS + 6), A_GPR(playback + 6), A_C_00000000, A_C_00000000); /* side left */
		A_OP(icode, &ptr, iACC3, A_GPR(playback + SND_EMU10K1_PLAYBACK_CHANNELS + 7), A_GPR(playback + 7), A_C_00000000, A_C_00000000); /* side right */
	पूर्ण
	

	ctl = &controls[nctl + 0];
	ctl->id.अगरace = (__क्रमce पूर्णांक)SNDRV_CTL_ELEM_IFACE_MIXER;
	म_नकल(ctl->id.name, "Tone Control - Bass");
	ctl->vcount = 2;
	ctl->count = 10;
	ctl->min = 0;
	ctl->max = 40;
	ctl->value[0] = ctl->value[1] = 20;
	ctl->translation = EMU10K1_GPR_TRANSLATION_BASS;
	ctl = &controls[nctl + 1];
	ctl->id.अगरace = (__क्रमce पूर्णांक)SNDRV_CTL_ELEM_IFACE_MIXER;
	म_नकल(ctl->id.name, "Tone Control - Treble");
	ctl->vcount = 2;
	ctl->count = 10;
	ctl->min = 0;
	ctl->max = 40;
	ctl->value[0] = ctl->value[1] = 20;
	ctl->translation = EMU10K1_GPR_TRANSLATION_TREBLE;

#घोषणा BASS_GPR	0x8c
#घोषणा TREBLE_GPR	0x96

	क्रम (z = 0; z < 5; z++) अणु
		पूर्णांक j;
		क्रम (j = 0; j < 2; j++) अणु
			controls[nctl + 0].gpr[z * 2 + j] = BASS_GPR + z * 2 + j;
			controls[nctl + 1].gpr[z * 2 + j] = TREBLE_GPR + z * 2 + j;
		पूर्ण
	पूर्ण
	क्रम (z = 0; z < 4; z++) अणु		/* front/rear/center-lfe/side */
		पूर्णांक j, k, l, d;
		क्रम (j = 0; j < 2; j++) अणु	/* left/right */
			k = 0xb0 + (z * 8) + (j * 4);
			l = 0xe0 + (z * 8) + (j * 4);
			d = playback + SND_EMU10K1_PLAYBACK_CHANNELS + z * 2 + j;

			A_OP(icode, &ptr, iMAC0, A_C_00000000, A_C_00000000, A_GPR(d), A_GPR(BASS_GPR + 0 + j));
			A_OP(icode, &ptr, iMACMV, A_GPR(k+1), A_GPR(k), A_GPR(k+1), A_GPR(BASS_GPR + 4 + j));
			A_OP(icode, &ptr, iMACMV, A_GPR(k), A_GPR(d), A_GPR(k), A_GPR(BASS_GPR + 2 + j));
			A_OP(icode, &ptr, iMACMV, A_GPR(k+3), A_GPR(k+2), A_GPR(k+3), A_GPR(BASS_GPR + 8 + j));
			A_OP(icode, &ptr, iMAC0, A_GPR(k+2), A_GPR_ACCU, A_GPR(k+2), A_GPR(BASS_GPR + 6 + j));
			A_OP(icode, &ptr, iACC3, A_GPR(k+2), A_GPR(k+2), A_GPR(k+2), A_C_00000000);

			A_OP(icode, &ptr, iMAC0, A_C_00000000, A_C_00000000, A_GPR(k+2), A_GPR(TREBLE_GPR + 0 + j));
			A_OP(icode, &ptr, iMACMV, A_GPR(l+1), A_GPR(l), A_GPR(l+1), A_GPR(TREBLE_GPR + 4 + j));
			A_OP(icode, &ptr, iMACMV, A_GPR(l), A_GPR(k+2), A_GPR(l), A_GPR(TREBLE_GPR + 2 + j));
			A_OP(icode, &ptr, iMACMV, A_GPR(l+3), A_GPR(l+2), A_GPR(l+3), A_GPR(TREBLE_GPR + 8 + j));
			A_OP(icode, &ptr, iMAC0, A_GPR(l+2), A_GPR_ACCU, A_GPR(l+2), A_GPR(TREBLE_GPR + 6 + j));
			A_OP(icode, &ptr, iMACINT0, A_GPR(l+2), A_C_00000000, A_GPR(l+2), A_C_00000010);

			A_OP(icode, &ptr, iACC3, A_GPR(d), A_GPR(l+2), A_C_00000000, A_C_00000000);

			अगर (z == 2)	/* center */
				अवरोध;
		पूर्ण
	पूर्ण
	nctl += 2;

#अघोषित BASS_GPR
#अघोषित TREBLE_GPR

	क्रम (z = 0; z < 8; z++) अणु
		A_SWITCH(icode, &ptr, पंचांगp + 0, playback + SND_EMU10K1_PLAYBACK_CHANNELS + z, gpr + 0);
		A_SWITCH_NEG(icode, &ptr, पंचांगp + 1, gpr + 0);
		A_SWITCH(icode, &ptr, पंचांगp + 1, playback + z, पंचांगp + 1);
		A_OP(icode, &ptr, iACC3, A_GPR(playback + SND_EMU10K1_PLAYBACK_CHANNELS + z), A_GPR(पंचांगp + 0), A_GPR(पंचांगp + 1), A_C_00000000);
	पूर्ण
	snd_emu10k1_init_stereo_onoff_control(controls + nctl++, "Tone Control - Switch", gpr, 0);
	gpr += 2;

	/* Master volume (will be नामd later) */
	A_OP(icode, &ptr, iMAC0, A_GPR(playback+0+SND_EMU10K1_PLAYBACK_CHANNELS), A_C_00000000, A_GPR(gpr), A_GPR(playback+0+SND_EMU10K1_PLAYBACK_CHANNELS));
	A_OP(icode, &ptr, iMAC0, A_GPR(playback+1+SND_EMU10K1_PLAYBACK_CHANNELS), A_C_00000000, A_GPR(gpr), A_GPR(playback+1+SND_EMU10K1_PLAYBACK_CHANNELS));
	A_OP(icode, &ptr, iMAC0, A_GPR(playback+2+SND_EMU10K1_PLAYBACK_CHANNELS), A_C_00000000, A_GPR(gpr), A_GPR(playback+2+SND_EMU10K1_PLAYBACK_CHANNELS));
	A_OP(icode, &ptr, iMAC0, A_GPR(playback+3+SND_EMU10K1_PLAYBACK_CHANNELS), A_C_00000000, A_GPR(gpr), A_GPR(playback+3+SND_EMU10K1_PLAYBACK_CHANNELS));
	A_OP(icode, &ptr, iMAC0, A_GPR(playback+4+SND_EMU10K1_PLAYBACK_CHANNELS), A_C_00000000, A_GPR(gpr), A_GPR(playback+4+SND_EMU10K1_PLAYBACK_CHANNELS));
	A_OP(icode, &ptr, iMAC0, A_GPR(playback+5+SND_EMU10K1_PLAYBACK_CHANNELS), A_C_00000000, A_GPR(gpr), A_GPR(playback+5+SND_EMU10K1_PLAYBACK_CHANNELS));
	A_OP(icode, &ptr, iMAC0, A_GPR(playback+6+SND_EMU10K1_PLAYBACK_CHANNELS), A_C_00000000, A_GPR(gpr), A_GPR(playback+6+SND_EMU10K1_PLAYBACK_CHANNELS));
	A_OP(icode, &ptr, iMAC0, A_GPR(playback+7+SND_EMU10K1_PLAYBACK_CHANNELS), A_C_00000000, A_GPR(gpr), A_GPR(playback+7+SND_EMU10K1_PLAYBACK_CHANNELS));
	snd_emu10k1_init_mono_control(&controls[nctl++], "Wave Master Playback Volume", gpr, 0);
	gpr += 2;

	/* analog speakers */
	A_PUT_STEREO_OUTPUT(A_EXTOUT_AFRONT_L, A_EXTOUT_AFRONT_R, playback + SND_EMU10K1_PLAYBACK_CHANNELS);
	A_PUT_STEREO_OUTPUT(A_EXTOUT_AREAR_L, A_EXTOUT_AREAR_R, playback+2 + SND_EMU10K1_PLAYBACK_CHANNELS);
	A_PUT_OUTPUT(A_EXTOUT_ACENTER, playback+4 + SND_EMU10K1_PLAYBACK_CHANNELS);
	A_PUT_OUTPUT(A_EXTOUT_ALFE, playback+5 + SND_EMU10K1_PLAYBACK_CHANNELS);
	अगर (emu->card_capabilities->spk71)
		A_PUT_STEREO_OUTPUT(A_EXTOUT_ASIDE_L, A_EXTOUT_ASIDE_R, playback+6 + SND_EMU10K1_PLAYBACK_CHANNELS);

	/* headphone */
	A_PUT_STEREO_OUTPUT(A_EXTOUT_HEADPHONE_L, A_EXTOUT_HEADPHONE_R, playback + SND_EMU10K1_PLAYBACK_CHANNELS);

	/* digital outमाला_दो */
	/* A_PUT_STEREO_OUTPUT(A_EXTOUT_FRONT_L, A_EXTOUT_FRONT_R, playback + SND_EMU10K1_PLAYBACK_CHANNELS); */
	अगर (emu->card_capabilities->emu_model) अणु
		/* EMU1010 Outमाला_दो from PCM Front, Rear, Center, LFE, Side */
		dev_info(emu->card->dev, "EMU outputs on\n");
		क्रम (z = 0; z < 8; z++) अणु
			अगर (emu->card_capabilities->ca0108_chip) अणु
				A_OP(icode, &ptr, iACC3, A3_EMU32OUT(z), A_GPR(playback + SND_EMU10K1_PLAYBACK_CHANNELS + z), A_C_00000000, A_C_00000000);
			पूर्ण अन्यथा अणु
				A_OP(icode, &ptr, iACC3, A_EMU32OUTL(z), A_GPR(playback + SND_EMU10K1_PLAYBACK_CHANNELS + z), A_C_00000000, A_C_00000000);
			पूर्ण
		पूर्ण
	पूर्ण

	/* IEC958 Optical Raw Playback Switch */ 
	gpr_map[gpr++] = 0;
	gpr_map[gpr++] = 0x1008;
	gpr_map[gpr++] = 0xffff0000;
	क्रम (z = 0; z < 2; z++) अणु
		A_OP(icode, &ptr, iMAC0, A_GPR(पंचांगp + 2), A_FXBUS(FXBUS_PT_LEFT + z), A_C_00000000, A_C_00000000);
		A_OP(icode, &ptr, iSKIP, A_GPR_COND, A_GPR_COND, A_GPR(gpr - 2), A_C_00000001);
		A_OP(icode, &ptr, iACC3, A_GPR(पंचांगp + 2), A_C_00000000, A_C_00010000, A_GPR(पंचांगp + 2));
		A_OP(icode, &ptr, iANDXOR, A_GPR(पंचांगp + 2), A_GPR(पंचांगp + 2), A_GPR(gpr - 1), A_C_00000000);
		A_SWITCH(icode, &ptr, पंचांगp + 0, पंचांगp + 2, gpr + z);
		A_SWITCH_NEG(icode, &ptr, पंचांगp + 1, gpr + z);
		A_SWITCH(icode, &ptr, पंचांगp + 1, playback + SND_EMU10K1_PLAYBACK_CHANNELS + z, पंचांगp + 1);
		अगर ((z==1) && (emu->card_capabilities->spdअगर_bug)) अणु
			/* Due to a SPDIF output bug on some Audigy cards, this code delays the Right channel by 1 sample */
			dev_info(emu->card->dev,
				 "Installing spdif_bug patch: %s\n",
				 emu->card_capabilities->name);
			A_OP(icode, &ptr, iACC3, A_EXTOUT(A_EXTOUT_FRONT_L + z), A_GPR(gpr - 3), A_C_00000000, A_C_00000000);
			A_OP(icode, &ptr, iACC3, A_GPR(gpr - 3), A_GPR(पंचांगp + 0), A_GPR(पंचांगp + 1), A_C_00000000);
		पूर्ण अन्यथा अणु
			A_OP(icode, &ptr, iACC3, A_EXTOUT(A_EXTOUT_FRONT_L + z), A_GPR(पंचांगp + 0), A_GPR(पंचांगp + 1), A_C_00000000);
		पूर्ण
	पूर्ण
	snd_emu10k1_init_stereo_onoff_control(controls + nctl++, SNDRV_CTL_NAME_IEC958("Optical Raw ",PLAYBACK,SWITCH), gpr, 0);
	gpr += 2;
	
	A_PUT_STEREO_OUTPUT(A_EXTOUT_REAR_L, A_EXTOUT_REAR_R, playback+2 + SND_EMU10K1_PLAYBACK_CHANNELS);
	A_PUT_OUTPUT(A_EXTOUT_CENTER, playback+4 + SND_EMU10K1_PLAYBACK_CHANNELS);
	A_PUT_OUTPUT(A_EXTOUT_LFE, playback+5 + SND_EMU10K1_PLAYBACK_CHANNELS);

	/* ADC buffer */
#अगर_घोषित EMU10K1_CAPTURE_DIGITAL_OUT
	A_PUT_STEREO_OUTPUT(A_EXTOUT_ADC_CAP_L, A_EXTOUT_ADC_CAP_R, playback + SND_EMU10K1_PLAYBACK_CHANNELS);
#अन्यथा
	A_PUT_OUTPUT(A_EXTOUT_ADC_CAP_L, capture);
	A_PUT_OUTPUT(A_EXTOUT_ADC_CAP_R, capture+1);
#पूर्ण_अगर

	अगर (emu->card_capabilities->emu_model) अणु
		अगर (emu->card_capabilities->ca0108_chip) अणु
			dev_info(emu->card->dev, "EMU2 inputs on\n");
			क्रम (z = 0; z < 0x10; z++) अणु
				snd_emu10k1_audigy_dsp_convert_32_to_2x16( icode, &ptr, पंचांगp, 
									bit_shअगरter16,
									A3_EMU32IN(z),
									A_FXBUS2(z*2) );
			पूर्ण
		पूर्ण अन्यथा अणु
			dev_info(emu->card->dev, "EMU inputs on\n");
			/* Capture 16 (originally 8) channels of S32_LE sound */

			/*
			dev_dbg(emu->card->dev, "emufx.c: gpr=0x%x, tmp=0x%x\n",
			       gpr, पंचांगp);
			*/
			/* For the EMU1010: How to get 32bit values from the DSP. High 16bits पूर्णांकo L, low 16bits पूर्णांकo R. */
			/* A_P16VIN(0) is delayed by one sample,
			 * so all other A_P16VIN channels will need to also be delayed
			 */
			/* Left ADC in. 1 of 2 */
			snd_emu10k1_audigy_dsp_convert_32_to_2x16( icode, &ptr, पंचांगp, bit_shअगरter16, A_P16VIN(0x0), A_FXBUS2(0) );
			/* Right ADC in 1 of 2 */
			gpr_map[gpr++] = 0x00000000;
			/* Delaying by one sample: instead of copying the input
			 * value A_P16VIN to output A_FXBUS2 as in the first channel,
			 * we use an auxiliary रेजिस्टर, delaying the value by one
			 * sample
			 */
			snd_emu10k1_audigy_dsp_convert_32_to_2x16( icode, &ptr, पंचांगp, bit_shअगरter16, A_GPR(gpr - 1), A_FXBUS2(2) );
			A_OP(icode, &ptr, iACC3, A_GPR(gpr - 1), A_P16VIN(0x1), A_C_00000000, A_C_00000000);
			gpr_map[gpr++] = 0x00000000;
			snd_emu10k1_audigy_dsp_convert_32_to_2x16( icode, &ptr, पंचांगp, bit_shअगरter16, A_GPR(gpr - 1), A_FXBUS2(4) );
			A_OP(icode, &ptr, iACC3, A_GPR(gpr - 1), A_P16VIN(0x2), A_C_00000000, A_C_00000000);
			gpr_map[gpr++] = 0x00000000;
			snd_emu10k1_audigy_dsp_convert_32_to_2x16( icode, &ptr, पंचांगp, bit_shअगरter16, A_GPR(gpr - 1), A_FXBUS2(6) );
			A_OP(icode, &ptr, iACC3, A_GPR(gpr - 1), A_P16VIN(0x3), A_C_00000000, A_C_00000000);
			/* For 96kHz mode */
			/* Left ADC in. 2 of 2 */
			gpr_map[gpr++] = 0x00000000;
			snd_emu10k1_audigy_dsp_convert_32_to_2x16( icode, &ptr, पंचांगp, bit_shअगरter16, A_GPR(gpr - 1), A_FXBUS2(0x8) );
			A_OP(icode, &ptr, iACC3, A_GPR(gpr - 1), A_P16VIN(0x4), A_C_00000000, A_C_00000000);
			/* Right ADC in 2 of 2 */
			gpr_map[gpr++] = 0x00000000;
			snd_emu10k1_audigy_dsp_convert_32_to_2x16( icode, &ptr, पंचांगp, bit_shअगरter16, A_GPR(gpr - 1), A_FXBUS2(0xa) );
			A_OP(icode, &ptr, iACC3, A_GPR(gpr - 1), A_P16VIN(0x5), A_C_00000000, A_C_00000000);
			gpr_map[gpr++] = 0x00000000;
			snd_emu10k1_audigy_dsp_convert_32_to_2x16( icode, &ptr, पंचांगp, bit_shअगरter16, A_GPR(gpr - 1), A_FXBUS2(0xc) );
			A_OP(icode, &ptr, iACC3, A_GPR(gpr - 1), A_P16VIN(0x6), A_C_00000000, A_C_00000000);
			gpr_map[gpr++] = 0x00000000;
			snd_emu10k1_audigy_dsp_convert_32_to_2x16( icode, &ptr, पंचांगp, bit_shअगरter16, A_GPR(gpr - 1), A_FXBUS2(0xe) );
			A_OP(icode, &ptr, iACC3, A_GPR(gpr - 1), A_P16VIN(0x7), A_C_00000000, A_C_00000000);
			/* Pavel Hofman - we still have voices, A_FXBUS2s, and
			 * A_P16VINs available -
			 * let's add 8 more capture channels - total of 16
			 */
			gpr_map[gpr++] = 0x00000000;
			snd_emu10k1_audigy_dsp_convert_32_to_2x16(icode, &ptr, पंचांगp,
								  bit_shअगरter16,
								  A_GPR(gpr - 1),
								  A_FXBUS2(0x10));
			A_OP(icode, &ptr, iACC3, A_GPR(gpr - 1), A_P16VIN(0x8),
			     A_C_00000000, A_C_00000000);
			gpr_map[gpr++] = 0x00000000;
			snd_emu10k1_audigy_dsp_convert_32_to_2x16(icode, &ptr, पंचांगp,
								  bit_shअगरter16,
								  A_GPR(gpr - 1),
								  A_FXBUS2(0x12));
			A_OP(icode, &ptr, iACC3, A_GPR(gpr - 1), A_P16VIN(0x9),
			     A_C_00000000, A_C_00000000);
			gpr_map[gpr++] = 0x00000000;
			snd_emu10k1_audigy_dsp_convert_32_to_2x16(icode, &ptr, पंचांगp,
								  bit_shअगरter16,
								  A_GPR(gpr - 1),
								  A_FXBUS2(0x14));
			A_OP(icode, &ptr, iACC3, A_GPR(gpr - 1), A_P16VIN(0xa),
			     A_C_00000000, A_C_00000000);
			gpr_map[gpr++] = 0x00000000;
			snd_emu10k1_audigy_dsp_convert_32_to_2x16(icode, &ptr, पंचांगp,
								  bit_shअगरter16,
								  A_GPR(gpr - 1),
								  A_FXBUS2(0x16));
			A_OP(icode, &ptr, iACC3, A_GPR(gpr - 1), A_P16VIN(0xb),
			     A_C_00000000, A_C_00000000);
			gpr_map[gpr++] = 0x00000000;
			snd_emu10k1_audigy_dsp_convert_32_to_2x16(icode, &ptr, पंचांगp,
								  bit_shअगरter16,
								  A_GPR(gpr - 1),
								  A_FXBUS2(0x18));
			A_OP(icode, &ptr, iACC3, A_GPR(gpr - 1), A_P16VIN(0xc),
			     A_C_00000000, A_C_00000000);
			gpr_map[gpr++] = 0x00000000;
			snd_emu10k1_audigy_dsp_convert_32_to_2x16(icode, &ptr, पंचांगp,
								  bit_shअगरter16,
								  A_GPR(gpr - 1),
								  A_FXBUS2(0x1a));
			A_OP(icode, &ptr, iACC3, A_GPR(gpr - 1), A_P16VIN(0xd),
			     A_C_00000000, A_C_00000000);
			gpr_map[gpr++] = 0x00000000;
			snd_emu10k1_audigy_dsp_convert_32_to_2x16(icode, &ptr, पंचांगp,
								  bit_shअगरter16,
								  A_GPR(gpr - 1),
								  A_FXBUS2(0x1c));
			A_OP(icode, &ptr, iACC3, A_GPR(gpr - 1), A_P16VIN(0xe),
			     A_C_00000000, A_C_00000000);
			gpr_map[gpr++] = 0x00000000;
			snd_emu10k1_audigy_dsp_convert_32_to_2x16(icode, &ptr, पंचांगp,
								  bit_shअगरter16,
								  A_GPR(gpr - 1),
								  A_FXBUS2(0x1e));
			A_OP(icode, &ptr, iACC3, A_GPR(gpr - 1), A_P16VIN(0xf),
			     A_C_00000000, A_C_00000000);
		पूर्ण

#अगर 0
		क्रम (z = 4; z < 8; z++) अणु
			A_OP(icode, &ptr, iACC3, A_FXBUS2(z), A_C_00000000, A_C_00000000, A_C_00000000);
		पूर्ण
		क्रम (z = 0xc; z < 0x10; z++) अणु
			A_OP(icode, &ptr, iACC3, A_FXBUS2(z), A_C_00000000, A_C_00000000, A_C_00000000);
		पूर्ण
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		/* EFX capture - capture the 16 EXTINs */
		/* Capture 16 channels of S16_LE sound */
		क्रम (z = 0; z < 16; z++) अणु
			A_OP(icode, &ptr, iACC3, A_FXBUS2(z), A_C_00000000, A_C_00000000, A_EXTIN(z));
		पूर्ण
	पूर्ण
	
#पूर्ण_अगर /* JCD test */
	/*
	 * ok, set up करोne..
	 */

	अगर (gpr > पंचांगp) अणु
		snd_BUG();
		err = -EIO;
		जाओ __err;
	पूर्ण
	/* clear reमुख्यing inकाष्ठाion memory */
	जबतक (ptr < 0x400)
		A_OP(icode, &ptr, 0x0f, 0xc0, 0xc0, 0xcf, 0xc0);

	icode->gpr_add_control_count = nctl;
	icode->gpr_add_controls = controls;
	emu->support_tlv = 1; /* support TLV */
	err = snd_emu10k1_icode_poke(emu, icode, true);
	emu->support_tlv = 0; /* clear again */

__err:
	kमुक्त(controls);
__err_ctrls:
	kमुक्त(icode->gpr_map);
__err_gpr:
	kमुक्त(icode);
	वापस err;
पूर्ण


/*
 * initial DSP configuration क्रम Emu10k1
 */

/* when volume = max, then copy only to aव्योम volume modअगरication */
/* with iMAC0 (negative values) */
अटल व्योम _volume(काष्ठा snd_emu10k1_fx8010_code *icode, u32 *ptr, u32 dst, u32 src, u32 vol)
अणु
	OP(icode, ptr, iMAC0, dst, C_00000000, src, vol);
	OP(icode, ptr, iANDXOR, C_00000000, vol, C_ffffffff, C_7fffffff);
	OP(icode, ptr, iSKIP, GPR_COND, GPR_COND, CC_REG_NONZERO, C_00000001);
	OP(icode, ptr, iACC3, dst, src, C_00000000, C_00000000);
पूर्ण
अटल व्योम _volume_add(काष्ठा snd_emu10k1_fx8010_code *icode, u32 *ptr, u32 dst, u32 src, u32 vol)
अणु
	OP(icode, ptr, iANDXOR, C_00000000, vol, C_ffffffff, C_7fffffff);
	OP(icode, ptr, iSKIP, GPR_COND, GPR_COND, CC_REG_NONZERO, C_00000002);
	OP(icode, ptr, iMACINT0, dst, dst, src, C_00000001);
	OP(icode, ptr, iSKIP, C_00000000, C_7fffffff, C_7fffffff, C_00000001);
	OP(icode, ptr, iMAC0, dst, dst, src, vol);
पूर्ण
अटल व्योम _volume_out(काष्ठा snd_emu10k1_fx8010_code *icode, u32 *ptr, u32 dst, u32 src, u32 vol)
अणु
	OP(icode, ptr, iANDXOR, C_00000000, vol, C_ffffffff, C_7fffffff);
	OP(icode, ptr, iSKIP, GPR_COND, GPR_COND, CC_REG_NONZERO, C_00000002);
	OP(icode, ptr, iACC3, dst, src, C_00000000, C_00000000);
	OP(icode, ptr, iSKIP, C_00000000, C_7fffffff, C_7fffffff, C_00000001);
	OP(icode, ptr, iMAC0, dst, C_00000000, src, vol);
पूर्ण

#घोषणा VOLUME(icode, ptr, dst, src, vol) \
		_volume(icode, ptr, GPR(dst), GPR(src), GPR(vol))
#घोषणा VOLUME_IN(icode, ptr, dst, src, vol) \
		_volume(icode, ptr, GPR(dst), EXTIN(src), GPR(vol))
#घोषणा VOLUME_ADD(icode, ptr, dst, src, vol) \
		_volume_add(icode, ptr, GPR(dst), GPR(src), GPR(vol))
#घोषणा VOLUME_ADDIN(icode, ptr, dst, src, vol) \
		_volume_add(icode, ptr, GPR(dst), EXTIN(src), GPR(vol))
#घोषणा VOLUME_OUT(icode, ptr, dst, src, vol) \
		_volume_out(icode, ptr, EXTOUT(dst), GPR(src), GPR(vol))
#घोषणा _SWITCH(icode, ptr, dst, src, sw) \
	OP((icode), ptr, iMACINT0, dst, C_00000000, src, sw);
#घोषणा SWITCH(icode, ptr, dst, src, sw) \
		_SWITCH(icode, ptr, GPR(dst), GPR(src), GPR(sw))
#घोषणा SWITCH_IN(icode, ptr, dst, src, sw) \
		_SWITCH(icode, ptr, GPR(dst), EXTIN(src), GPR(sw))
#घोषणा _SWITCH_NEG(icode, ptr, dst, src) \
	OP((icode), ptr, iANDXOR, dst, src, C_00000001, C_00000001);
#घोषणा SWITCH_NEG(icode, ptr, dst, src) \
		_SWITCH_NEG(icode, ptr, GPR(dst), GPR(src))


अटल पूर्णांक _snd_emu10k1_init_efx(काष्ठा snd_emu10k1 *emu)
अणु
	पूर्णांक err, i, z, gpr, पंचांगp, playback, capture;
	u32 ptr;
	काष्ठा snd_emu10k1_fx8010_code *icode;
	काष्ठा snd_emu10k1_fx8010_pcm_rec *ipcm = शून्य;
	काष्ठा snd_emu10k1_fx8010_control_gpr *controls = शून्य, *ctl;
	u32 *gpr_map;

	err = -ENOMEM;
	icode = kzalloc(माप(*icode), GFP_KERNEL);
	अगर (!icode)
		वापस err;

	icode->gpr_map = kसुस्मृति(256 + 160 + 160 + 2 * 512,
				 माप(u_पूर्णांक32_t), GFP_KERNEL);
	अगर (!icode->gpr_map)
		जाओ __err_gpr;

	controls = kसुस्मृति(SND_EMU10K1_GPR_CONTROLS,
			   माप(काष्ठा snd_emu10k1_fx8010_control_gpr),
			   GFP_KERNEL);
	अगर (!controls)
		जाओ __err_ctrls;

	ipcm = kzalloc(माप(*ipcm), GFP_KERNEL);
	अगर (!ipcm)
		जाओ __err_ipcm;

	gpr_map = icode->gpr_map;

	icode->tram_data_map = icode->gpr_map + 256;
	icode->tram_addr_map = icode->tram_data_map + 160;
	icode->code = icode->tram_addr_map + 160;
	
	/* clear मुक्त GPRs */
	क्रम (i = 0; i < 256; i++)
		set_bit(i, icode->gpr_valid);

	/* clear TRAM data & address lines */
	क्रम (i = 0; i < 160; i++)
		set_bit(i, icode->tram_valid);

	म_नकल(icode->name, "SB Live! FX8010 code for ALSA v1.2 by Jaroslav Kysela");
	ptr = 0; i = 0;
	/* we have 12 inमाला_दो */
	playback = SND_EMU10K1_INPUTS;
	/* we have 6 playback channels and tone control द्विगुनs */
	capture = playback + (SND_EMU10K1_PLAYBACK_CHANNELS * 2);
	gpr = capture + SND_EMU10K1_CAPTURE_CHANNELS;
	पंचांगp = 0x88;	/* we need 4 temporary GPR */
	/* from 0x8c to 0xff is the area क्रम tone control */

	/* stop FX processor */
	snd_emu10k1_ptr_ग_लिखो(emu, DBG, 0, (emu->fx8010.dbg = 0) | EMU10K1_DBG_SINGLE_STEP);

	/*
	 *  Process FX Buses
	 */
	OP(icode, &ptr, iMACINT0, GPR(0), C_00000000, FXBUS(FXBUS_PCM_LEFT), C_00000004);
	OP(icode, &ptr, iMACINT0, GPR(1), C_00000000, FXBUS(FXBUS_PCM_RIGHT), C_00000004);
	OP(icode, &ptr, iMACINT0, GPR(2), C_00000000, FXBUS(FXBUS_MIDI_LEFT), C_00000004);
	OP(icode, &ptr, iMACINT0, GPR(3), C_00000000, FXBUS(FXBUS_MIDI_RIGHT), C_00000004);
	OP(icode, &ptr, iMACINT0, GPR(4), C_00000000, FXBUS(FXBUS_PCM_LEFT_REAR), C_00000004);
	OP(icode, &ptr, iMACINT0, GPR(5), C_00000000, FXBUS(FXBUS_PCM_RIGHT_REAR), C_00000004);
	OP(icode, &ptr, iMACINT0, GPR(6), C_00000000, FXBUS(FXBUS_PCM_CENTER), C_00000004);
	OP(icode, &ptr, iMACINT0, GPR(7), C_00000000, FXBUS(FXBUS_PCM_LFE), C_00000004);
	OP(icode, &ptr, iMACINT0, GPR(8), C_00000000, C_00000000, C_00000000);	/* S/PDIF left */
	OP(icode, &ptr, iMACINT0, GPR(9), C_00000000, C_00000000, C_00000000);	/* S/PDIF right */
	OP(icode, &ptr, iMACINT0, GPR(10), C_00000000, FXBUS(FXBUS_PCM_LEFT_FRONT), C_00000004);
	OP(icode, &ptr, iMACINT0, GPR(11), C_00000000, FXBUS(FXBUS_PCM_RIGHT_FRONT), C_00000004);

	/* Raw S/PDIF PCM */
	ipcm->substream = 0;
	ipcm->channels = 2;
	ipcm->tram_start = 0;
	ipcm->buffer_size = (64 * 1024) / 2;
	ipcm->gpr_size = gpr++;
	ipcm->gpr_ptr = gpr++;
	ipcm->gpr_count = gpr++;
	ipcm->gpr_पंचांगpcount = gpr++;
	ipcm->gpr_trigger = gpr++;
	ipcm->gpr_running = gpr++;
	ipcm->etram[0] = 0;
	ipcm->etram[1] = 1;

	gpr_map[gpr + 0] = 0xfffff000;
	gpr_map[gpr + 1] = 0xffff0000;
	gpr_map[gpr + 2] = 0x70000000;
	gpr_map[gpr + 3] = 0x00000007;
	gpr_map[gpr + 4] = 0x001f << 11;
	gpr_map[gpr + 5] = 0x001c << 11;
	gpr_map[gpr + 6] = (0x22  - 0x01) - 1;	/* skip at 01 to 22 */
	gpr_map[gpr + 7] = (0x22  - 0x06) - 1;	/* skip at 06 to 22 */
	gpr_map[gpr + 8] = 0x2000000 + (2<<11);
	gpr_map[gpr + 9] = 0x4000000 + (2<<11);
	gpr_map[gpr + 10] = 1<<11;
	gpr_map[gpr + 11] = (0x24 - 0x0a) - 1;	/* skip at 0a to 24 */
	gpr_map[gpr + 12] = 0;

	/* अगर the trigger flag is not set, skip */
	/* 00: */ OP(icode, &ptr, iMAC0, C_00000000, GPR(ipcm->gpr_trigger), C_00000000, C_00000000);
	/* 01: */ OP(icode, &ptr, iSKIP, GPR_COND, GPR_COND, CC_REG_ZERO, GPR(gpr + 6));
	/* अगर the running flag is set, we're running */
	/* 02: */ OP(icode, &ptr, iMAC0, C_00000000, GPR(ipcm->gpr_running), C_00000000, C_00000000);
	/* 03: */ OP(icode, &ptr, iSKIP, GPR_COND, GPR_COND, CC_REG_NONZERO, C_00000004);
	/* रुको until ((GPR_DBAC>>11) & 0x1f) == 0x1c) */
	/* 04: */ OP(icode, &ptr, iANDXOR, GPR(पंचांगp + 0), GPR_DBAC, GPR(gpr + 4), C_00000000);
	/* 05: */ OP(icode, &ptr, iMACINT0, C_00000000, GPR(पंचांगp + 0), C_ffffffff, GPR(gpr + 5));
	/* 06: */ OP(icode, &ptr, iSKIP, GPR_COND, GPR_COND, CC_REG_NONZERO, GPR(gpr + 7));
	/* 07: */ OP(icode, &ptr, iACC3, GPR(gpr + 12), C_00000010, C_00000001, C_00000000);

	/* 08: */ OP(icode, &ptr, iANDXOR, GPR(ipcm->gpr_running), GPR(ipcm->gpr_running), C_00000000, C_00000001);
	/* 09: */ OP(icode, &ptr, iACC3, GPR(gpr + 12), GPR(gpr + 12), C_ffffffff, C_00000000);
	/* 0a: */ OP(icode, &ptr, iSKIP, GPR_COND, GPR_COND, CC_REG_NONZERO, GPR(gpr + 11));
	/* 0b: */ OP(icode, &ptr, iACC3, GPR(gpr + 12), C_00000001, C_00000000, C_00000000);

	/* 0c: */ OP(icode, &ptr, iANDXOR, GPR(पंचांगp + 0), ETRAM_DATA(ipcm->etram[0]), GPR(gpr + 0), C_00000000);
	/* 0d: */ OP(icode, &ptr, iLOG, GPR(पंचांगp + 0), GPR(पंचांगp + 0), GPR(gpr + 3), C_00000000);
	/* 0e: */ OP(icode, &ptr, iANDXOR, GPR(8), GPR(पंचांगp + 0), GPR(gpr + 1), GPR(gpr + 2));
	/* 0f: */ OP(icode, &ptr, iSKIP, C_00000000, GPR_COND, CC_REG_MINUS, C_00000001);
	/* 10: */ OP(icode, &ptr, iANDXOR, GPR(8), GPR(8), GPR(gpr + 1), GPR(gpr + 2));

	/* 11: */ OP(icode, &ptr, iANDXOR, GPR(पंचांगp + 0), ETRAM_DATA(ipcm->etram[1]), GPR(gpr + 0), C_00000000);
	/* 12: */ OP(icode, &ptr, iLOG, GPR(पंचांगp + 0), GPR(पंचांगp + 0), GPR(gpr + 3), C_00000000);
	/* 13: */ OP(icode, &ptr, iANDXOR, GPR(9), GPR(पंचांगp + 0), GPR(gpr + 1), GPR(gpr + 2));
	/* 14: */ OP(icode, &ptr, iSKIP, C_00000000, GPR_COND, CC_REG_MINUS, C_00000001);
	/* 15: */ OP(icode, &ptr, iANDXOR, GPR(9), GPR(9), GPR(gpr + 1), GPR(gpr + 2));

	/* 16: */ OP(icode, &ptr, iACC3, GPR(पंचांगp + 0), GPR(ipcm->gpr_ptr), C_00000001, C_00000000);
	/* 17: */ OP(icode, &ptr, iMACINT0, C_00000000, GPR(पंचांगp + 0), C_ffffffff, GPR(ipcm->gpr_size));
	/* 18: */ OP(icode, &ptr, iSKIP, GPR_COND, GPR_COND, CC_REG_MINUS, C_00000001);
	/* 19: */ OP(icode, &ptr, iACC3, GPR(पंचांगp + 0), C_00000000, C_00000000, C_00000000);
	/* 1a: */ OP(icode, &ptr, iACC3, GPR(ipcm->gpr_ptr), GPR(पंचांगp + 0), C_00000000, C_00000000);
	
	/* 1b: */ OP(icode, &ptr, iACC3, GPR(ipcm->gpr_पंचांगpcount), GPR(ipcm->gpr_पंचांगpcount), C_ffffffff, C_00000000);
	/* 1c: */ OP(icode, &ptr, iSKIP, GPR_COND, GPR_COND, CC_REG_NONZERO, C_00000002);
	/* 1d: */ OP(icode, &ptr, iACC3, GPR(ipcm->gpr_पंचांगpcount), GPR(ipcm->gpr_count), C_00000000, C_00000000);
	/* 1e: */ OP(icode, &ptr, iACC3, GPR_IRQ, C_80000000, C_00000000, C_00000000);
	/* 1f: */ OP(icode, &ptr, iANDXOR, GPR(ipcm->gpr_running), GPR(ipcm->gpr_running), C_00000001, C_00010000);

	/* 20: */ OP(icode, &ptr, iANDXOR, GPR(ipcm->gpr_running), GPR(ipcm->gpr_running), C_00010000, C_00000001);
	/* 21: */ OP(icode, &ptr, iSKIP, C_00000000, C_7fffffff, C_7fffffff, C_00000002);

	/* 22: */ OP(icode, &ptr, iMACINT1, ETRAM_ADDR(ipcm->etram[0]), GPR(gpr + 8), GPR_DBAC, C_ffffffff);
	/* 23: */ OP(icode, &ptr, iMACINT1, ETRAM_ADDR(ipcm->etram[1]), GPR(gpr + 9), GPR_DBAC, C_ffffffff);

	/* 24: */
	gpr += 13;

	/* Wave Playback Volume */
	क्रम (z = 0; z < 2; z++)
		VOLUME(icode, &ptr, playback + z, z, gpr + z);
	snd_emu10k1_init_stereo_control(controls + i++, "Wave Playback Volume", gpr, 100);
	gpr += 2;

	/* Wave Surround Playback Volume */
	क्रम (z = 0; z < 2; z++)
		VOLUME(icode, &ptr, playback + 2 + z, z, gpr + z);
	snd_emu10k1_init_stereo_control(controls + i++, "Wave Surround Playback Volume", gpr, 0);
	gpr += 2;
	
	/* Wave Center/LFE Playback Volume */
	OP(icode, &ptr, iACC3, GPR(पंचांगp + 0), FXBUS(FXBUS_PCM_LEFT), FXBUS(FXBUS_PCM_RIGHT), C_00000000);
	OP(icode, &ptr, iMACINT0, GPR(पंचांगp + 0), C_00000000, GPR(पंचांगp + 0), C_00000002);
	VOLUME(icode, &ptr, playback + 4, पंचांगp + 0, gpr);
	snd_emu10k1_init_mono_control(controls + i++, "Wave Center Playback Volume", gpr++, 0);
	VOLUME(icode, &ptr, playback + 5, पंचांगp + 0, gpr);
	snd_emu10k1_init_mono_control(controls + i++, "Wave LFE Playback Volume", gpr++, 0);

	/* Wave Capture Volume + Switch */
	क्रम (z = 0; z < 2; z++) अणु
		SWITCH(icode, &ptr, पंचांगp + 0, z, gpr + 2 + z);
		VOLUME(icode, &ptr, capture + z, पंचांगp + 0, gpr + z);
	पूर्ण
	snd_emu10k1_init_stereo_control(controls + i++, "Wave Capture Volume", gpr, 0);
	snd_emu10k1_init_stereo_onoff_control(controls + i++, "Wave Capture Switch", gpr + 2, 0);
	gpr += 4;

	/* Synth Playback Volume */
	क्रम (z = 0; z < 2; z++)
		VOLUME_ADD(icode, &ptr, playback + z, 2 + z, gpr + z);
	snd_emu10k1_init_stereo_control(controls + i++, "Synth Playback Volume", gpr, 100);
	gpr += 2;

	/* Synth Capture Volume + Switch */
	क्रम (z = 0; z < 2; z++) अणु
		SWITCH(icode, &ptr, पंचांगp + 0, 2 + z, gpr + 2 + z);
		VOLUME_ADD(icode, &ptr, capture + z, पंचांगp + 0, gpr + z);
	पूर्ण
	snd_emu10k1_init_stereo_control(controls + i++, "Synth Capture Volume", gpr, 0);
	snd_emu10k1_init_stereo_onoff_control(controls + i++, "Synth Capture Switch", gpr + 2, 0);
	gpr += 4;

	/* Surround Digital Playback Volume (नामd later without Digital) */
	क्रम (z = 0; z < 2; z++)
		VOLUME_ADD(icode, &ptr, playback + 2 + z, 4 + z, gpr + z);
	snd_emu10k1_init_stereo_control(controls + i++, "Surround Digital Playback Volume", gpr, 100);
	gpr += 2;

	/* Surround Capture Volume + Switch */
	क्रम (z = 0; z < 2; z++) अणु
		SWITCH(icode, &ptr, पंचांगp + 0, 4 + z, gpr + 2 + z);
		VOLUME_ADD(icode, &ptr, capture + z, पंचांगp + 0, gpr + z);
	पूर्ण
	snd_emu10k1_init_stereo_control(controls + i++, "Surround Capture Volume", gpr, 0);
	snd_emu10k1_init_stereo_onoff_control(controls + i++, "Surround Capture Switch", gpr + 2, 0);
	gpr += 4;

	/* Center Playback Volume (नामd later without Digital) */
	VOLUME_ADD(icode, &ptr, playback + 4, 6, gpr);
	snd_emu10k1_init_mono_control(controls + i++, "Center Digital Playback Volume", gpr++, 100);

	/* LFE Playback Volume + Switch (नामd later without Digital) */
	VOLUME_ADD(icode, &ptr, playback + 5, 7, gpr);
	snd_emu10k1_init_mono_control(controls + i++, "LFE Digital Playback Volume", gpr++, 100);

	/* Front Playback Volume */
	क्रम (z = 0; z < 2; z++)
		VOLUME_ADD(icode, &ptr, playback + z, 10 + z, gpr + z);
	snd_emu10k1_init_stereo_control(controls + i++, "Front Playback Volume", gpr, 100);
	gpr += 2;

	/* Front Capture Volume + Switch */
	क्रम (z = 0; z < 2; z++) अणु
		SWITCH(icode, &ptr, पंचांगp + 0, 10 + z, gpr + 2);
		VOLUME_ADD(icode, &ptr, capture + z, पंचांगp + 0, gpr + z);
	पूर्ण
	snd_emu10k1_init_stereo_control(controls + i++, "Front Capture Volume", gpr, 0);
	snd_emu10k1_init_mono_onoff_control(controls + i++, "Front Capture Switch", gpr + 2, 0);
	gpr += 3;

	/*
	 *  Process inमाला_दो
	 */

	अगर (emu->fx8010.extin_mask & ((1<<EXTIN_AC97_L)|(1<<EXTIN_AC97_R))) अणु
		/* AC'97 Playback Volume */
		VOLUME_ADDIN(icode, &ptr, playback + 0, EXTIN_AC97_L, gpr); gpr++;
		VOLUME_ADDIN(icode, &ptr, playback + 1, EXTIN_AC97_R, gpr); gpr++;
		snd_emu10k1_init_stereo_control(controls + i++, "AC97 Playback Volume", gpr-2, 0);
		/* AC'97 Capture Volume */
		VOLUME_ADDIN(icode, &ptr, capture + 0, EXTIN_AC97_L, gpr); gpr++;
		VOLUME_ADDIN(icode, &ptr, capture + 1, EXTIN_AC97_R, gpr); gpr++;
		snd_emu10k1_init_stereo_control(controls + i++, "AC97 Capture Volume", gpr-2, 100);
	पूर्ण
	
	अगर (emu->fx8010.extin_mask & ((1<<EXTIN_SPDIF_CD_L)|(1<<EXTIN_SPDIF_CD_R))) अणु
		/* IEC958 TTL Playback Volume */
		क्रम (z = 0; z < 2; z++)
			VOLUME_ADDIN(icode, &ptr, playback + z, EXTIN_SPDIF_CD_L + z, gpr + z);
		snd_emu10k1_init_stereo_control(controls + i++, SNDRV_CTL_NAME_IEC958("TTL ",PLAYBACK,VOLUME), gpr, 0);
		gpr += 2;
	
		/* IEC958 TTL Capture Volume + Switch */
		क्रम (z = 0; z < 2; z++) अणु
			SWITCH_IN(icode, &ptr, पंचांगp + 0, EXTIN_SPDIF_CD_L + z, gpr + 2 + z);
			VOLUME_ADD(icode, &ptr, capture + z, पंचांगp + 0, gpr + z);
		पूर्ण
		snd_emu10k1_init_stereo_control(controls + i++, SNDRV_CTL_NAME_IEC958("TTL ",CAPTURE,VOLUME), gpr, 0);
		snd_emu10k1_init_stereo_onoff_control(controls + i++, SNDRV_CTL_NAME_IEC958("TTL ",CAPTURE,SWITCH), gpr + 2, 0);
		gpr += 4;
	पूर्ण
	
	अगर (emu->fx8010.extin_mask & ((1<<EXTIN_ZOOM_L)|(1<<EXTIN_ZOOM_R))) अणु
		/* Zoom Video Playback Volume */
		क्रम (z = 0; z < 2; z++)
			VOLUME_ADDIN(icode, &ptr, playback + z, EXTIN_ZOOM_L + z, gpr + z);
		snd_emu10k1_init_stereo_control(controls + i++, "Zoom Video Playback Volume", gpr, 0);
		gpr += 2;
	
		/* Zoom Video Capture Volume + Switch */
		क्रम (z = 0; z < 2; z++) अणु
			SWITCH_IN(icode, &ptr, पंचांगp + 0, EXTIN_ZOOM_L + z, gpr + 2 + z);
			VOLUME_ADD(icode, &ptr, capture + z, पंचांगp + 0, gpr + z);
		पूर्ण
		snd_emu10k1_init_stereo_control(controls + i++, "Zoom Video Capture Volume", gpr, 0);
		snd_emu10k1_init_stereo_onoff_control(controls + i++, "Zoom Video Capture Switch", gpr + 2, 0);
		gpr += 4;
	पूर्ण
	
	अगर (emu->fx8010.extin_mask & ((1<<EXTIN_TOSLINK_L)|(1<<EXTIN_TOSLINK_R))) अणु
		/* IEC958 Optical Playback Volume */
		क्रम (z = 0; z < 2; z++)
			VOLUME_ADDIN(icode, &ptr, playback + z, EXTIN_TOSLINK_L + z, gpr + z);
		snd_emu10k1_init_stereo_control(controls + i++, SNDRV_CTL_NAME_IEC958("LiveDrive ",PLAYBACK,VOLUME), gpr, 0);
		gpr += 2;
	
		/* IEC958 Optical Capture Volume */
		क्रम (z = 0; z < 2; z++) अणु
			SWITCH_IN(icode, &ptr, पंचांगp + 0, EXTIN_TOSLINK_L + z, gpr + 2 + z);
			VOLUME_ADD(icode, &ptr, capture + z, पंचांगp + 0, gpr + z);
		पूर्ण
		snd_emu10k1_init_stereo_control(controls + i++, SNDRV_CTL_NAME_IEC958("LiveDrive ",CAPTURE,VOLUME), gpr, 0);
		snd_emu10k1_init_stereo_onoff_control(controls + i++, SNDRV_CTL_NAME_IEC958("LiveDrive ",CAPTURE,SWITCH), gpr + 2, 0);
		gpr += 4;
	पूर्ण
	
	अगर (emu->fx8010.extin_mask & ((1<<EXTIN_LINE1_L)|(1<<EXTIN_LINE1_R))) अणु
		/* Line LiveDrive Playback Volume */
		क्रम (z = 0; z < 2; z++)
			VOLUME_ADDIN(icode, &ptr, playback + z, EXTIN_LINE1_L + z, gpr + z);
		snd_emu10k1_init_stereo_control(controls + i++, "Line LiveDrive Playback Volume", gpr, 0);
		gpr += 2;
	
		/* Line LiveDrive Capture Volume + Switch */
		क्रम (z = 0; z < 2; z++) अणु
			SWITCH_IN(icode, &ptr, पंचांगp + 0, EXTIN_LINE1_L + z, gpr + 2 + z);
			VOLUME_ADD(icode, &ptr, capture + z, पंचांगp + 0, gpr + z);
		पूर्ण
		snd_emu10k1_init_stereo_control(controls + i++, "Line LiveDrive Capture Volume", gpr, 0);
		snd_emu10k1_init_stereo_onoff_control(controls + i++, "Line LiveDrive Capture Switch", gpr + 2, 0);
		gpr += 4;
	पूर्ण
	
	अगर (emu->fx8010.extin_mask & ((1<<EXTIN_COAX_SPDIF_L)|(1<<EXTIN_COAX_SPDIF_R))) अणु
		/* IEC958 Coax Playback Volume */
		क्रम (z = 0; z < 2; z++)
			VOLUME_ADDIN(icode, &ptr, playback + z, EXTIN_COAX_SPDIF_L + z, gpr + z);
		snd_emu10k1_init_stereo_control(controls + i++, SNDRV_CTL_NAME_IEC958("Coaxial ",PLAYBACK,VOLUME), gpr, 0);
		gpr += 2;
	
		/* IEC958 Coax Capture Volume + Switch */
		क्रम (z = 0; z < 2; z++) अणु
			SWITCH_IN(icode, &ptr, पंचांगp + 0, EXTIN_COAX_SPDIF_L + z, gpr + 2 + z);
			VOLUME_ADD(icode, &ptr, capture + z, पंचांगp + 0, gpr + z);
		पूर्ण
		snd_emu10k1_init_stereo_control(controls + i++, SNDRV_CTL_NAME_IEC958("Coaxial ",CAPTURE,VOLUME), gpr, 0);
		snd_emu10k1_init_stereo_onoff_control(controls + i++, SNDRV_CTL_NAME_IEC958("Coaxial ",CAPTURE,SWITCH), gpr + 2, 0);
		gpr += 4;
	पूर्ण
	
	अगर (emu->fx8010.extin_mask & ((1<<EXTIN_LINE2_L)|(1<<EXTIN_LINE2_R))) अणु
		/* Line LiveDrive Playback Volume */
		क्रम (z = 0; z < 2; z++)
			VOLUME_ADDIN(icode, &ptr, playback + z, EXTIN_LINE2_L + z, gpr + z);
		snd_emu10k1_init_stereo_control(controls + i++, "Line2 LiveDrive Playback Volume", gpr, 0);
		controls[i-1].id.index = 1;
		gpr += 2;
	
		/* Line LiveDrive Capture Volume */
		क्रम (z = 0; z < 2; z++) अणु
			SWITCH_IN(icode, &ptr, पंचांगp + 0, EXTIN_LINE2_L + z, gpr + 2 + z);
			VOLUME_ADD(icode, &ptr, capture + z, पंचांगp + 0, gpr + z);
		पूर्ण
		snd_emu10k1_init_stereo_control(controls + i++, "Line2 LiveDrive Capture Volume", gpr, 0);
		controls[i-1].id.index = 1;
		snd_emu10k1_init_stereo_onoff_control(controls + i++, "Line2 LiveDrive Capture Switch", gpr + 2, 0);
		controls[i-1].id.index = 1;
		gpr += 4;
	पूर्ण

	/*
	 *  Process tone control
	 */
	OP(icode, &ptr, iACC3, GPR(playback + SND_EMU10K1_PLAYBACK_CHANNELS + 0), GPR(playback + 0), C_00000000, C_00000000); /* left */
	OP(icode, &ptr, iACC3, GPR(playback + SND_EMU10K1_PLAYBACK_CHANNELS + 1), GPR(playback + 1), C_00000000, C_00000000); /* right */
	OP(icode, &ptr, iACC3, GPR(playback + SND_EMU10K1_PLAYBACK_CHANNELS + 2), GPR(playback + 2), C_00000000, C_00000000); /* rear left */
	OP(icode, &ptr, iACC3, GPR(playback + SND_EMU10K1_PLAYBACK_CHANNELS + 3), GPR(playback + 3), C_00000000, C_00000000); /* rear right */
	OP(icode, &ptr, iACC3, GPR(playback + SND_EMU10K1_PLAYBACK_CHANNELS + 4), GPR(playback + 4), C_00000000, C_00000000); /* center */
	OP(icode, &ptr, iACC3, GPR(playback + SND_EMU10K1_PLAYBACK_CHANNELS + 5), GPR(playback + 5), C_00000000, C_00000000); /* LFE */

	ctl = &controls[i + 0];
	ctl->id.अगरace = (__क्रमce पूर्णांक)SNDRV_CTL_ELEM_IFACE_MIXER;
	म_नकल(ctl->id.name, "Tone Control - Bass");
	ctl->vcount = 2;
	ctl->count = 10;
	ctl->min = 0;
	ctl->max = 40;
	ctl->value[0] = ctl->value[1] = 20;
	ctl->tlv = snd_emu10k1_bass_treble_db_scale;
	ctl->translation = EMU10K1_GPR_TRANSLATION_BASS;
	ctl = &controls[i + 1];
	ctl->id.अगरace = (__क्रमce पूर्णांक)SNDRV_CTL_ELEM_IFACE_MIXER;
	म_नकल(ctl->id.name, "Tone Control - Treble");
	ctl->vcount = 2;
	ctl->count = 10;
	ctl->min = 0;
	ctl->max = 40;
	ctl->value[0] = ctl->value[1] = 20;
	ctl->tlv = snd_emu10k1_bass_treble_db_scale;
	ctl->translation = EMU10K1_GPR_TRANSLATION_TREBLE;

#घोषणा BASS_GPR	0x8c
#घोषणा TREBLE_GPR	0x96

	क्रम (z = 0; z < 5; z++) अणु
		पूर्णांक j;
		क्रम (j = 0; j < 2; j++) अणु
			controls[i + 0].gpr[z * 2 + j] = BASS_GPR + z * 2 + j;
			controls[i + 1].gpr[z * 2 + j] = TREBLE_GPR + z * 2 + j;
		पूर्ण
	पूर्ण
	क्रम (z = 0; z < 3; z++) अणु		/* front/rear/center-lfe */
		पूर्णांक j, k, l, d;
		क्रम (j = 0; j < 2; j++) अणु	/* left/right */
			k = 0xa0 + (z * 8) + (j * 4);
			l = 0xd0 + (z * 8) + (j * 4);
			d = playback + SND_EMU10K1_PLAYBACK_CHANNELS + z * 2 + j;

			OP(icode, &ptr, iMAC0, C_00000000, C_00000000, GPR(d), GPR(BASS_GPR + 0 + j));
			OP(icode, &ptr, iMACMV, GPR(k+1), GPR(k), GPR(k+1), GPR(BASS_GPR + 4 + j));
			OP(icode, &ptr, iMACMV, GPR(k), GPR(d), GPR(k), GPR(BASS_GPR + 2 + j));
			OP(icode, &ptr, iMACMV, GPR(k+3), GPR(k+2), GPR(k+3), GPR(BASS_GPR + 8 + j));
			OP(icode, &ptr, iMAC0, GPR(k+2), GPR_ACCU, GPR(k+2), GPR(BASS_GPR + 6 + j));
			OP(icode, &ptr, iACC3, GPR(k+2), GPR(k+2), GPR(k+2), C_00000000);

			OP(icode, &ptr, iMAC0, C_00000000, C_00000000, GPR(k+2), GPR(TREBLE_GPR + 0 + j));
			OP(icode, &ptr, iMACMV, GPR(l+1), GPR(l), GPR(l+1), GPR(TREBLE_GPR + 4 + j));
			OP(icode, &ptr, iMACMV, GPR(l), GPR(k+2), GPR(l), GPR(TREBLE_GPR + 2 + j));
			OP(icode, &ptr, iMACMV, GPR(l+3), GPR(l+2), GPR(l+3), GPR(TREBLE_GPR + 8 + j));
			OP(icode, &ptr, iMAC0, GPR(l+2), GPR_ACCU, GPR(l+2), GPR(TREBLE_GPR + 6 + j));
			OP(icode, &ptr, iMACINT0, GPR(l+2), C_00000000, GPR(l+2), C_00000010);

			OP(icode, &ptr, iACC3, GPR(d), GPR(l+2), C_00000000, C_00000000);

			अगर (z == 2)	/* center */
				अवरोध;
		पूर्ण
	पूर्ण
	i += 2;

#अघोषित BASS_GPR
#अघोषित TREBLE_GPR

	क्रम (z = 0; z < 6; z++) अणु
		SWITCH(icode, &ptr, पंचांगp + 0, playback + SND_EMU10K1_PLAYBACK_CHANNELS + z, gpr + 0);
		SWITCH_NEG(icode, &ptr, पंचांगp + 1, gpr + 0);
		SWITCH(icode, &ptr, पंचांगp + 1, playback + z, पंचांगp + 1);
		OP(icode, &ptr, iACC3, GPR(playback + SND_EMU10K1_PLAYBACK_CHANNELS + z), GPR(पंचांगp + 0), GPR(पंचांगp + 1), C_00000000);
	पूर्ण
	snd_emu10k1_init_stereo_onoff_control(controls + i++, "Tone Control - Switch", gpr, 0);
	gpr += 2;

	/*
	 *  Process outमाला_दो
	 */
	अगर (emu->fx8010.extout_mask & ((1<<EXTOUT_AC97_L)|(1<<EXTOUT_AC97_R))) अणु
		/* AC'97 Playback Volume */

		क्रम (z = 0; z < 2; z++)
			OP(icode, &ptr, iACC3, EXTOUT(EXTOUT_AC97_L + z), GPR(playback + SND_EMU10K1_PLAYBACK_CHANNELS + z), C_00000000, C_00000000);
	पूर्ण

	अगर (emu->fx8010.extout_mask & ((1<<EXTOUT_TOSLINK_L)|(1<<EXTOUT_TOSLINK_R))) अणु
		/* IEC958 Optical Raw Playback Switch */

		क्रम (z = 0; z < 2; z++) अणु
			SWITCH(icode, &ptr, पंचांगp + 0, 8 + z, gpr + z);
			SWITCH_NEG(icode, &ptr, पंचांगp + 1, gpr + z);
			SWITCH(icode, &ptr, पंचांगp + 1, playback + SND_EMU10K1_PLAYBACK_CHANNELS + z, पंचांगp + 1);
			OP(icode, &ptr, iACC3, EXTOUT(EXTOUT_TOSLINK_L + z), GPR(पंचांगp + 0), GPR(पंचांगp + 1), C_00000000);
#अगर_घोषित EMU10K1_CAPTURE_DIGITAL_OUT
	 		OP(icode, &ptr, iACC3, EXTOUT(EXTOUT_ADC_CAP_L + z), GPR(पंचांगp + 0), GPR(पंचांगp + 1), C_00000000);
#पूर्ण_अगर
		पूर्ण

		snd_emu10k1_init_stereo_onoff_control(controls + i++, SNDRV_CTL_NAME_IEC958("Optical Raw ",PLAYBACK,SWITCH), gpr, 0);
		gpr += 2;
	पूर्ण

	अगर (emu->fx8010.extout_mask & ((1<<EXTOUT_HEADPHONE_L)|(1<<EXTOUT_HEADPHONE_R))) अणु
		/* Headphone Playback Volume */

		क्रम (z = 0; z < 2; z++) अणु
			SWITCH(icode, &ptr, पंचांगp + 0, playback + SND_EMU10K1_PLAYBACK_CHANNELS + 4 + z, gpr + 2 + z);
			SWITCH_NEG(icode, &ptr, पंचांगp + 1, gpr + 2 + z);
			SWITCH(icode, &ptr, पंचांगp + 1, playback + SND_EMU10K1_PLAYBACK_CHANNELS + z, पंचांगp + 1);
			OP(icode, &ptr, iACC3, GPR(पंचांगp + 0), GPR(पंचांगp + 0), GPR(पंचांगp + 1), C_00000000);
			VOLUME_OUT(icode, &ptr, EXTOUT_HEADPHONE_L + z, पंचांगp + 0, gpr + z);
		पूर्ण

		snd_emu10k1_init_stereo_control(controls + i++, "Headphone Playback Volume", gpr + 0, 0);
		controls[i-1].id.index = 1;	/* AC'97 can have also Headphone control */
		snd_emu10k1_init_mono_onoff_control(controls + i++, "Headphone Center Playback Switch", gpr + 2, 0);
		controls[i-1].id.index = 1;
		snd_emu10k1_init_mono_onoff_control(controls + i++, "Headphone LFE Playback Switch", gpr + 3, 0);
		controls[i-1].id.index = 1;

		gpr += 4;
	पूर्ण
	
	अगर (emu->fx8010.extout_mask & ((1<<EXTOUT_REAR_L)|(1<<EXTOUT_REAR_R)))
		क्रम (z = 0; z < 2; z++)
			OP(icode, &ptr, iACC3, EXTOUT(EXTOUT_REAR_L + z), GPR(playback + SND_EMU10K1_PLAYBACK_CHANNELS + 2 + z), C_00000000, C_00000000);

	अगर (emu->fx8010.extout_mask & ((1<<EXTOUT_AC97_REAR_L)|(1<<EXTOUT_AC97_REAR_R)))
		क्रम (z = 0; z < 2; z++)
			OP(icode, &ptr, iACC3, EXTOUT(EXTOUT_AC97_REAR_L + z), GPR(playback + SND_EMU10K1_PLAYBACK_CHANNELS + 2 + z), C_00000000, C_00000000);

	अगर (emu->fx8010.extout_mask & (1<<EXTOUT_AC97_CENTER)) अणु
#अगर_अघोषित EMU10K1_CENTER_LFE_FROM_FRONT
		OP(icode, &ptr, iACC3, EXTOUT(EXTOUT_AC97_CENTER), GPR(playback + SND_EMU10K1_PLAYBACK_CHANNELS + 4), C_00000000, C_00000000);
		OP(icode, &ptr, iACC3, EXTOUT(EXTOUT_ACENTER), GPR(playback + SND_EMU10K1_PLAYBACK_CHANNELS + 4), C_00000000, C_00000000);
#अन्यथा
		OP(icode, &ptr, iACC3, EXTOUT(EXTOUT_AC97_CENTER), GPR(playback + SND_EMU10K1_PLAYBACK_CHANNELS + 0), C_00000000, C_00000000);
		OP(icode, &ptr, iACC3, EXTOUT(EXTOUT_ACENTER), GPR(playback + SND_EMU10K1_PLAYBACK_CHANNELS + 0), C_00000000, C_00000000);
#पूर्ण_अगर
	पूर्ण

	अगर (emu->fx8010.extout_mask & (1<<EXTOUT_AC97_LFE)) अणु
#अगर_अघोषित EMU10K1_CENTER_LFE_FROM_FRONT
		OP(icode, &ptr, iACC3, EXTOUT(EXTOUT_AC97_LFE), GPR(playback + SND_EMU10K1_PLAYBACK_CHANNELS + 5), C_00000000, C_00000000);
		OP(icode, &ptr, iACC3, EXTOUT(EXTOUT_ALFE), GPR(playback + SND_EMU10K1_PLAYBACK_CHANNELS + 5), C_00000000, C_00000000);
#अन्यथा
		OP(icode, &ptr, iACC3, EXTOUT(EXTOUT_AC97_LFE), GPR(playback + SND_EMU10K1_PLAYBACK_CHANNELS + 1), C_00000000, C_00000000);
		OP(icode, &ptr, iACC3, EXTOUT(EXTOUT_ALFE), GPR(playback + SND_EMU10K1_PLAYBACK_CHANNELS + 1), C_00000000, C_00000000);
#पूर्ण_अगर
	पूर्ण
	
#अगर_अघोषित EMU10K1_CAPTURE_DIGITAL_OUT
	क्रम (z = 0; z < 2; z++)
 		OP(icode, &ptr, iACC3, EXTOUT(EXTOUT_ADC_CAP_L + z), GPR(capture + z), C_00000000, C_00000000);
#पूर्ण_अगर
	
	अगर (emu->fx8010.extout_mask & (1<<EXTOUT_MIC_CAP))
		OP(icode, &ptr, iACC3, EXTOUT(EXTOUT_MIC_CAP), GPR(capture + 2), C_00000000, C_00000000);

	/* EFX capture - capture the 16 EXTINS */
	अगर (emu->card_capabilities->sblive51) अणु
		/* On the Live! 5.1, FXBUS2(1) and FXBUS(2) are shared with EXTOUT_ACENTER
		 * and EXTOUT_ALFE, so we can't connect inमाला_दो to them क्रम multitrack recording.
		 *
		 * Since only 14 of the 16 EXTINs are used, this is not a big problem.  
		 * We route AC97L and R to FX capture 14 and 15, SPDIF CD in to FX capture 
		 * 0 and 3, then the rest of the EXTINs to the corresponding FX capture 
		 * channel.  Multitrack recorders will still see the center/lfe output संकेत 
		 * on the second and third channels.
		 */
		OP(icode, &ptr, iACC3, FXBUS2(14), C_00000000, C_00000000, EXTIN(0));
		OP(icode, &ptr, iACC3, FXBUS2(15), C_00000000, C_00000000, EXTIN(1));
		OP(icode, &ptr, iACC3, FXBUS2(0), C_00000000, C_00000000, EXTIN(2));
		OP(icode, &ptr, iACC3, FXBUS2(3), C_00000000, C_00000000, EXTIN(3));
		क्रम (z = 4; z < 14; z++)
			OP(icode, &ptr, iACC3, FXBUS2(z), C_00000000, C_00000000, EXTIN(z));
	पूर्ण अन्यथा अणु
		क्रम (z = 0; z < 16; z++)
			OP(icode, &ptr, iACC3, FXBUS2(z), C_00000000, C_00000000, EXTIN(z));
	पूर्ण
	    

	अगर (gpr > पंचांगp) अणु
		snd_BUG();
		err = -EIO;
		जाओ __err;
	पूर्ण
	अगर (i > SND_EMU10K1_GPR_CONTROLS) अणु
		snd_BUG();
		err = -EIO;
		जाओ __err;
	पूर्ण
	
	/* clear reमुख्यing inकाष्ठाion memory */
	जबतक (ptr < 0x200)
		OP(icode, &ptr, iACC3, C_00000000, C_00000000, C_00000000, C_00000000);

	अगर ((err = snd_emu10k1_fx8010_tram_setup(emu, ipcm->buffer_size)) < 0)
		जाओ __err;
	icode->gpr_add_control_count = i;
	icode->gpr_add_controls = controls;
	emu->support_tlv = 1; /* support TLV */
	err = snd_emu10k1_icode_poke(emu, icode, true);
	emu->support_tlv = 0; /* clear again */
	अगर (err >= 0)
		err = snd_emu10k1_ipcm_poke(emu, ipcm);
__err:
	kमुक्त(ipcm);
__err_ipcm:
	kमुक्त(controls);
__err_ctrls:
	kमुक्त(icode->gpr_map);
__err_gpr:
	kमुक्त(icode);
	वापस err;
पूर्ण

पूर्णांक snd_emu10k1_init_efx(काष्ठा snd_emu10k1 *emu)
अणु
	spin_lock_init(&emu->fx8010.irq_lock);
	INIT_LIST_HEAD(&emu->fx8010.gpr_ctl);
	अगर (emu->audigy)
		वापस _snd_emu10k1_audigy_init_efx(emu);
	अन्यथा
		वापस _snd_emu10k1_init_efx(emu);
पूर्ण

व्योम snd_emu10k1_मुक्त_efx(काष्ठा snd_emu10k1 *emu)
अणु
	/* stop processor */
	अगर (emu->audigy)
		snd_emu10k1_ptr_ग_लिखो(emu, A_DBG, 0, emu->fx8010.dbg = A_DBG_SINGLE_STEP);
	अन्यथा
		snd_emu10k1_ptr_ग_लिखो(emu, DBG, 0, emu->fx8010.dbg = EMU10K1_DBG_SINGLE_STEP);
पूर्ण

#अगर 0 /* FIXME: who use them? */
पूर्णांक snd_emu10k1_fx8010_tone_control_activate(काष्ठा snd_emu10k1 *emu, पूर्णांक output)
अणु
	अगर (output < 0 || output >= 6)
		वापस -EINVAL;
	snd_emu10k1_ptr_ग_लिखो(emu, emu->gpr_base + 0x94 + output, 0, 1);
	वापस 0;
पूर्ण

पूर्णांक snd_emu10k1_fx8010_tone_control_deactivate(काष्ठा snd_emu10k1 *emu, पूर्णांक output)
अणु
	अगर (output < 0 || output >= 6)
		वापस -EINVAL;
	snd_emu10k1_ptr_ग_लिखो(emu, emu->gpr_base + 0x94 + output, 0, 0);
	वापस 0;
पूर्ण
#पूर्ण_अगर

पूर्णांक snd_emu10k1_fx8010_tram_setup(काष्ठा snd_emu10k1 *emu, u32 size)
अणु
	u8 size_reg = 0;

	/* size is in samples */
	अगर (size != 0) अणु
		size = (size - 1) >> 13;

		जबतक (size) अणु
			size >>= 1;
			size_reg++;
		पूर्ण
		size = 0x2000 << size_reg;
	पूर्ण
	अगर ((emu->fx8010.etram_pages.bytes / 2) == size)
		वापस 0;
	spin_lock_irq(&emu->emu_lock);
	outl(HCFG_LOCKTANKCACHE_MASK | inl(emu->port + HCFG), emu->port + HCFG);
	spin_unlock_irq(&emu->emu_lock);
	snd_emu10k1_ptr_ग_लिखो(emu, TCB, 0, 0);
	snd_emu10k1_ptr_ग_लिखो(emu, TCBS, 0, 0);
	अगर (emu->fx8010.etram_pages.area != शून्य) अणु
		snd_dma_मुक्त_pages(&emu->fx8010.etram_pages);
		emu->fx8010.etram_pages.area = शून्य;
		emu->fx8010.etram_pages.bytes = 0;
	पूर्ण

	अगर (size > 0) अणु
		अगर (snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, &emu->pci->dev,
					size * 2, &emu->fx8010.etram_pages) < 0)
			वापस -ENOMEM;
		स_रखो(emu->fx8010.etram_pages.area, 0, size * 2);
		snd_emu10k1_ptr_ग_लिखो(emu, TCB, 0, emu->fx8010.etram_pages.addr);
		snd_emu10k1_ptr_ग_लिखो(emu, TCBS, 0, size_reg);
		spin_lock_irq(&emu->emu_lock);
		outl(inl(emu->port + HCFG) & ~HCFG_LOCKTANKCACHE_MASK, emu->port + HCFG);
		spin_unlock_irq(&emu->emu_lock);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1_fx8010_खोलो(काष्ठा snd_hwdep * hw, काष्ठा file *file)
अणु
	वापस 0;
पूर्ण

अटल व्योम copy_string(अक्षर *dst, स्थिर अक्षर *src, स्थिर अक्षर *null, पूर्णांक idx)
अणु
	अगर (src == शून्य)
		प्र_लिखो(dst, "%s %02X", null, idx);
	अन्यथा
		म_नकल(dst, src);
पूर्ण

अटल व्योम snd_emu10k1_fx8010_info(काष्ठा snd_emu10k1 *emu,
				   काष्ठा snd_emu10k1_fx8010_info *info)
अणु
	स्थिर अक्षर * स्थिर *fxbus, * स्थिर *extin, * स्थिर *extout;
	अचिन्हित लघु fxbus_mask, extin_mask, extout_mask;
	पूर्णांक res;

	info->पूर्णांकernal_tram_size = emu->fx8010.itram_size;
	info->बाह्यal_tram_size = emu->fx8010.etram_pages.bytes / 2;
	fxbus = fxbuses;
	extin = emu->audigy ? audigy_ins : creative_ins;
	extout = emu->audigy ? audigy_outs : creative_outs;
	fxbus_mask = emu->fx8010.fxbus_mask;
	extin_mask = emu->fx8010.extin_mask;
	extout_mask = emu->fx8010.extout_mask;
	क्रम (res = 0; res < 16; res++, fxbus++, extin++, extout++) अणु
		copy_string(info->fxbus_names[res], fxbus_mask & (1 << res) ? *fxbus : शून्य, "FXBUS", res);
		copy_string(info->extin_names[res], extin_mask & (1 << res) ? *extin : शून्य, "Unused", res);
		copy_string(info->extout_names[res], extout_mask & (1 << res) ? *extout : शून्य, "Unused", res);
	पूर्ण
	क्रम (res = 16; res < 32; res++, extout++)
		copy_string(info->extout_names[res], extout_mask & (1 << res) ? *extout : शून्य, "Unused", res);
	info->gpr_controls = emu->fx8010.gpr_count;
पूर्ण

अटल पूर्णांक snd_emu10k1_fx8010_ioctl(काष्ठा snd_hwdep * hw, काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा snd_emu10k1 *emu = hw->निजी_data;
	काष्ठा snd_emu10k1_fx8010_info *info;
	काष्ठा snd_emu10k1_fx8010_code *icode;
	काष्ठा snd_emu10k1_fx8010_pcm_rec *ipcm;
	अचिन्हित पूर्णांक addr;
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक res;
	
	चयन (cmd) अणु
	हाल SNDRV_EMU10K1_IOCTL_PVERSION:
		emu->support_tlv = 1;
		वापस put_user(SNDRV_EMU10K1_VERSION, (पूर्णांक __user *)argp);
	हाल SNDRV_EMU10K1_IOCTL_INFO:
		info = kzalloc(माप(*info), GFP_KERNEL);
		अगर (!info)
			वापस -ENOMEM;
		snd_emu10k1_fx8010_info(emu, info);
		अगर (copy_to_user(argp, info, माप(*info))) अणु
			kमुक्त(info);
			वापस -EFAULT;
		पूर्ण
		kमुक्त(info);
		वापस 0;
	हाल SNDRV_EMU10K1_IOCTL_CODE_POKE:
		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EPERM;

		icode = memdup_user(argp, माप(*icode));
		अगर (IS_ERR(icode))
			वापस PTR_ERR(icode);
		res = snd_emu10k1_icode_poke(emu, icode, false);
		kमुक्त(icode);
		वापस res;
	हाल SNDRV_EMU10K1_IOCTL_CODE_PEEK:
		icode = memdup_user(argp, माप(*icode));
		अगर (IS_ERR(icode))
			वापस PTR_ERR(icode);
		res = snd_emu10k1_icode_peek(emu, icode);
		अगर (res == 0 && copy_to_user(argp, icode, माप(*icode))) अणु
			kमुक्त(icode);
			वापस -EFAULT;
		पूर्ण
		kमुक्त(icode);
		वापस res;
	हाल SNDRV_EMU10K1_IOCTL_PCM_POKE:
		ipcm = memdup_user(argp, माप(*ipcm));
		अगर (IS_ERR(ipcm))
			वापस PTR_ERR(ipcm);
		res = snd_emu10k1_ipcm_poke(emu, ipcm);
		kमुक्त(ipcm);
		वापस res;
	हाल SNDRV_EMU10K1_IOCTL_PCM_PEEK:
		ipcm = memdup_user(argp, माप(*ipcm));
		अगर (IS_ERR(ipcm))
			वापस PTR_ERR(ipcm);
		res = snd_emu10k1_ipcm_peek(emu, ipcm);
		अगर (res == 0 && copy_to_user(argp, ipcm, माप(*ipcm))) अणु
			kमुक्त(ipcm);
			वापस -EFAULT;
		पूर्ण
		kमुक्त(ipcm);
		वापस res;
	हाल SNDRV_EMU10K1_IOCTL_TRAM_SETUP:
		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EPERM;
		अगर (get_user(addr, (अचिन्हित पूर्णांक __user *)argp))
			वापस -EFAULT;
		mutex_lock(&emu->fx8010.lock);
		res = snd_emu10k1_fx8010_tram_setup(emu, addr);
		mutex_unlock(&emu->fx8010.lock);
		वापस res;
	हाल SNDRV_EMU10K1_IOCTL_STOP:
		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EPERM;
		अगर (emu->audigy)
			snd_emu10k1_ptr_ग_लिखो(emu, A_DBG, 0, emu->fx8010.dbg |= A_DBG_SINGLE_STEP);
		अन्यथा
			snd_emu10k1_ptr_ग_लिखो(emu, DBG, 0, emu->fx8010.dbg |= EMU10K1_DBG_SINGLE_STEP);
		वापस 0;
	हाल SNDRV_EMU10K1_IOCTL_CONTINUE:
		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EPERM;
		अगर (emu->audigy)
			snd_emu10k1_ptr_ग_लिखो(emu, A_DBG, 0, emu->fx8010.dbg = 0);
		अन्यथा
			snd_emu10k1_ptr_ग_लिखो(emu, DBG, 0, emu->fx8010.dbg = 0);
		वापस 0;
	हाल SNDRV_EMU10K1_IOCTL_ZERO_TRAM_COUNTER:
		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EPERM;
		अगर (emu->audigy)
			snd_emu10k1_ptr_ग_लिखो(emu, A_DBG, 0, emu->fx8010.dbg | A_DBG_ZC);
		अन्यथा
			snd_emu10k1_ptr_ग_लिखो(emu, DBG, 0, emu->fx8010.dbg | EMU10K1_DBG_ZC);
		udelay(10);
		अगर (emu->audigy)
			snd_emu10k1_ptr_ग_लिखो(emu, A_DBG, 0, emu->fx8010.dbg);
		अन्यथा
			snd_emu10k1_ptr_ग_लिखो(emu, DBG, 0, emu->fx8010.dbg);
		वापस 0;
	हाल SNDRV_EMU10K1_IOCTL_SINGLE_STEP:
		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EPERM;
		अगर (get_user(addr, (अचिन्हित पूर्णांक __user *)argp))
			वापस -EFAULT;
		अगर (addr > 0x1ff)
			वापस -EINVAL;
		अगर (emu->audigy)
			snd_emu10k1_ptr_ग_लिखो(emu, A_DBG, 0, emu->fx8010.dbg |= A_DBG_SINGLE_STEP | addr);
		अन्यथा
			snd_emu10k1_ptr_ग_लिखो(emu, DBG, 0, emu->fx8010.dbg |= EMU10K1_DBG_SINGLE_STEP | addr);
		udelay(10);
		अगर (emu->audigy)
			snd_emu10k1_ptr_ग_लिखो(emu, A_DBG, 0, emu->fx8010.dbg |= A_DBG_SINGLE_STEP | A_DBG_STEP_ADDR | addr);
		अन्यथा
			snd_emu10k1_ptr_ग_लिखो(emu, DBG, 0, emu->fx8010.dbg |= EMU10K1_DBG_SINGLE_STEP | EMU10K1_DBG_STEP | addr);
		वापस 0;
	हाल SNDRV_EMU10K1_IOCTL_DBG_READ:
		अगर (emu->audigy)
			addr = snd_emu10k1_ptr_पढ़ो(emu, A_DBG, 0);
		अन्यथा
			addr = snd_emu10k1_ptr_पढ़ो(emu, DBG, 0);
		अगर (put_user(addr, (अचिन्हित पूर्णांक __user *)argp))
			वापस -EFAULT;
		वापस 0;
	पूर्ण
	वापस -ENOTTY;
पूर्ण

अटल पूर्णांक snd_emu10k1_fx8010_release(काष्ठा snd_hwdep * hw, काष्ठा file *file)
अणु
	वापस 0;
पूर्ण

पूर्णांक snd_emu10k1_fx8010_new(काष्ठा snd_emu10k1 *emu, पूर्णांक device)
अणु
	काष्ठा snd_hwdep *hw;
	पूर्णांक err;
	
	अगर ((err = snd_hwdep_new(emu->card, "FX8010", device, &hw)) < 0)
		वापस err;
	म_नकल(hw->name, "EMU10K1 (FX8010)");
	hw->अगरace = SNDRV_HWDEP_IFACE_EMU10K1;
	hw->ops.खोलो = snd_emu10k1_fx8010_खोलो;
	hw->ops.ioctl = snd_emu10k1_fx8010_ioctl;
	hw->ops.release = snd_emu10k1_fx8010_release;
	hw->निजी_data = emu;
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
पूर्णांक snd_emu10k1_efx_alloc_pm_buffer(काष्ठा snd_emu10k1 *emu)
अणु
	पूर्णांक len;

	len = emu->audigy ? 0x200 : 0x100;
	emu->saved_gpr = kदो_स्मृति_array(len, 4, GFP_KERNEL);
	अगर (! emu->saved_gpr)
		वापस -ENOMEM;
	len = emu->audigy ? 0x100 : 0xa0;
	emu->tram_val_saved = kदो_स्मृति_array(len, 4, GFP_KERNEL);
	emu->tram_addr_saved = kदो_स्मृति_array(len, 4, GFP_KERNEL);
	अगर (! emu->tram_val_saved || ! emu->tram_addr_saved)
		वापस -ENOMEM;
	len = emu->audigy ? 2 * 1024 : 2 * 512;
	emu->saved_icode = vदो_स्मृति(array_size(len, 4));
	अगर (! emu->saved_icode)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

व्योम snd_emu10k1_efx_मुक्त_pm_buffer(काष्ठा snd_emu10k1 *emu)
अणु
	kमुक्त(emu->saved_gpr);
	kमुक्त(emu->tram_val_saved);
	kमुक्त(emu->tram_addr_saved);
	vमुक्त(emu->saved_icode);
पूर्ण

/*
 * save/restore GPR, TRAM and codes
 */
व्योम snd_emu10k1_efx_suspend(काष्ठा snd_emu10k1 *emu)
अणु
	पूर्णांक i, len;

	len = emu->audigy ? 0x200 : 0x100;
	क्रम (i = 0; i < len; i++)
		emu->saved_gpr[i] = snd_emu10k1_ptr_पढ़ो(emu, emu->gpr_base + i, 0);

	len = emu->audigy ? 0x100 : 0xa0;
	क्रम (i = 0; i < len; i++) अणु
		emu->tram_val_saved[i] = snd_emu10k1_ptr_पढ़ो(emu, TANKMEMDATAREGBASE + i, 0);
		emu->tram_addr_saved[i] = snd_emu10k1_ptr_पढ़ो(emu, TANKMEMADDRREGBASE + i, 0);
		अगर (emu->audigy) अणु
			emu->tram_addr_saved[i] >>= 12;
			emu->tram_addr_saved[i] |=
				snd_emu10k1_ptr_पढ़ो(emu, A_TANKMEMCTLREGBASE + i, 0) << 20;
		पूर्ण
	पूर्ण

	len = emu->audigy ? 2 * 1024 : 2 * 512;
	क्रम (i = 0; i < len; i++)
		emu->saved_icode[i] = snd_emu10k1_efx_पढ़ो(emu, i);
पूर्ण

व्योम snd_emu10k1_efx_resume(काष्ठा snd_emu10k1 *emu)
अणु
	पूर्णांक i, len;

	/* set up TRAM */
	अगर (emu->fx8010.etram_pages.bytes > 0) अणु
		अचिन्हित size, size_reg = 0;
		size = emu->fx8010.etram_pages.bytes / 2;
		size = (size - 1) >> 13;
		जबतक (size) अणु
			size >>= 1;
			size_reg++;
		पूर्ण
		outl(HCFG_LOCKTANKCACHE_MASK | inl(emu->port + HCFG), emu->port + HCFG);
		snd_emu10k1_ptr_ग_लिखो(emu, TCB, 0, emu->fx8010.etram_pages.addr);
		snd_emu10k1_ptr_ग_लिखो(emu, TCBS, 0, size_reg);
		outl(inl(emu->port + HCFG) & ~HCFG_LOCKTANKCACHE_MASK, emu->port + HCFG);
	पूर्ण

	अगर (emu->audigy)
		snd_emu10k1_ptr_ग_लिखो(emu, A_DBG, 0, emu->fx8010.dbg | A_DBG_SINGLE_STEP);
	अन्यथा
		snd_emu10k1_ptr_ग_लिखो(emu, DBG, 0, emu->fx8010.dbg | EMU10K1_DBG_SINGLE_STEP);

	len = emu->audigy ? 0x200 : 0x100;
	क्रम (i = 0; i < len; i++)
		snd_emu10k1_ptr_ग_लिखो(emu, emu->gpr_base + i, 0, emu->saved_gpr[i]);

	len = emu->audigy ? 0x100 : 0xa0;
	क्रम (i = 0; i < len; i++) अणु
		snd_emu10k1_ptr_ग_लिखो(emu, TANKMEMDATAREGBASE + i, 0,
				      emu->tram_val_saved[i]);
		अगर (! emu->audigy)
			snd_emu10k1_ptr_ग_लिखो(emu, TANKMEMADDRREGBASE + i, 0,
					      emu->tram_addr_saved[i]);
		अन्यथा अणु
			snd_emu10k1_ptr_ग_लिखो(emu, TANKMEMADDRREGBASE + i, 0,
					      emu->tram_addr_saved[i] << 12);
			snd_emu10k1_ptr_ग_लिखो(emu, TANKMEMADDRREGBASE + i, 0,
					      emu->tram_addr_saved[i] >> 20);
		पूर्ण
	पूर्ण

	len = emu->audigy ? 2 * 1024 : 2 * 512;
	क्रम (i = 0; i < len; i++)
		snd_emu10k1_efx_ग_लिखो(emu, i, emu->saved_icode[i]);

	/* start FX processor when the DSP code is updated */
	अगर (emu->audigy)
		snd_emu10k1_ptr_ग_लिखो(emu, A_DBG, 0, emu->fx8010.dbg);
	अन्यथा
		snd_emu10k1_ptr_ग_लिखो(emu, DBG, 0, emu->fx8010.dbg);
पूर्ण
#पूर्ण_अगर
