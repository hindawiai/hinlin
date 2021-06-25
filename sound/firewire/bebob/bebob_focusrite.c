<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * bebob_focusrite.c - a part of driver क्रम BeBoB based devices
 *
 * Copyright (c) 2013-2014 Takashi Sakamoto
 */

#समावेश "./bebob.h"

#घोषणा ANA_IN	"Analog In"
#घोषणा DIG_IN	"Digital In"
#घोषणा ANA_OUT	"Analog Out"
#घोषणा DIG_OUT	"Digital Out"
#घोषणा STM_IN	"Stream In"

#घोषणा SAFFIRE_ADDRESS_BASE			0x000100000000ULL

#घोषणा SAFFIRE_OFFSET_CLOCK_SOURCE		0x00f8
#घोषणा SAFFIREPRO_OFFSET_CLOCK_SOURCE		0x0174

/* whether sync to बाह्यal device or not */
#घोषणा SAFFIRE_OFFSET_CLOCK_SYNC_EXT		0x013c
#घोषणा SAFFIRE_LE_OFFSET_CLOCK_SYNC_EXT	0x0432
#घोषणा SAFFIREPRO_OFFSET_CLOCK_SYNC_EXT	0x0164

#घोषणा SAFFIRE_CLOCK_SOURCE_INTERNAL		0
#घोषणा SAFFIRE_CLOCK_SOURCE_SPDIF		1

/* घड़ी sources as वापसed from रेजिस्टर of Saffire Pro 10 and 26 */
#घोषणा SAFFIREPRO_CLOCK_SOURCE_SELECT_MASK	0x000000ff
#घोषणा SAFFIREPRO_CLOCK_SOURCE_DETECT_MASK	0x0000ff00
#घोषणा SAFFIREPRO_CLOCK_SOURCE_INTERNAL	0
#घोषणा SAFFIREPRO_CLOCK_SOURCE_SKIP		1 /* never used on hardware */
#घोषणा SAFFIREPRO_CLOCK_SOURCE_SPDIF		2
#घोषणा SAFFIREPRO_CLOCK_SOURCE_ADAT1		3 /* not used on s.pro. 10 */
#घोषणा SAFFIREPRO_CLOCK_SOURCE_ADAT2		4 /* not used on s.pro. 10 */
#घोषणा SAFFIREPRO_CLOCK_SOURCE_WORDCLOCK	5
#घोषणा SAFFIREPRO_CLOCK_SOURCE_COUNT		6

/* S/PDIF, ADAT1, ADAT2 is enabled or not. three quadlets */
#घोषणा SAFFIREPRO_ENABLE_DIG_IFACES		0x01a4

/* saffirepro has its own parameter क्रम sampling frequency */
#घोषणा SAFFIREPRO_RATE_NOREBOOT		0x01cc
/* index is the value क्रम this रेजिस्टर */
अटल स्थिर अचिन्हित पूर्णांक rates[] = अणु
	[0] = 0,
	[1] = 44100,
	[2] = 48000,
	[3] = 88200,
	[4] = 96000,
	[5] = 176400,
	[6] = 192000
पूर्ण;

/* saffire(no label)/saffire LE has metering */
#घोषणा SAFFIRE_OFFSET_METER			0x0100
#घोषणा SAFFIRE_LE_OFFSET_METER			0x0168

अटल अंतरभूत पूर्णांक
saffire_पढ़ो_block(काष्ठा snd_bebob *bebob, u64 offset,
		   u32 *buf, अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err;
	__be32 *पंचांगp = (__be32 *)buf;

	err =  snd_fw_transaction(bebob->unit, TCODE_READ_BLOCK_REQUEST,
				  SAFFIRE_ADDRESS_BASE + offset,
				  पंचांगp, size, 0);
	अगर (err < 0)
		जाओ end;

	क्रम (i = 0; i < size / माप(u32); i++)
		buf[i] = be32_to_cpu(पंचांगp[i]);
end:
	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक
saffire_पढ़ो_quad(काष्ठा snd_bebob *bebob, u64 offset, u32 *value)
अणु
	पूर्णांक err;
	__be32 पंचांगp;

	err = snd_fw_transaction(bebob->unit, TCODE_READ_QUADLET_REQUEST,
				 SAFFIRE_ADDRESS_BASE + offset,
				 &पंचांगp, माप(__be32), 0);
	अगर (err < 0)
		जाओ end;

	*value = be32_to_cpu(पंचांगp);
end:
	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक
saffire_ग_लिखो_quad(काष्ठा snd_bebob *bebob, u64 offset, u32 value)
अणु
	__be32 data = cpu_to_be32(value);

	वापस snd_fw_transaction(bebob->unit, TCODE_WRITE_QUADLET_REQUEST,
				  SAFFIRE_ADDRESS_BASE + offset,
				  &data, माप(__be32), 0);
पूर्ण

अटल स्थिर क्रमागत snd_bebob_घड़ी_प्रकारype saffirepro_10_clk_src_types[] = अणु
	SND_BEBOB_CLOCK_TYPE_INTERNAL,
	SND_BEBOB_CLOCK_TYPE_EXTERNAL,	/* S/PDIF */
	SND_BEBOB_CLOCK_TYPE_EXTERNAL,	/* Word Clock */
पूर्ण;
अटल स्थिर क्रमागत snd_bebob_घड़ी_प्रकारype saffirepro_26_clk_src_types[] = अणु
	SND_BEBOB_CLOCK_TYPE_INTERNAL,
	SND_BEBOB_CLOCK_TYPE_EXTERNAL,	/* S/PDIF */
	SND_BEBOB_CLOCK_TYPE_EXTERNAL,	/* ADAT1 */
	SND_BEBOB_CLOCK_TYPE_EXTERNAL,	/* ADAT2 */
	SND_BEBOB_CLOCK_TYPE_EXTERNAL,	/* Word Clock */
पूर्ण;
/* Value maps between रेजिस्टरs and labels क्रम SaffirePro 10/26. */
अटल स्थिर चिन्हित अक्षर saffirepro_clk_maps[][SAFFIREPRO_CLOCK_SOURCE_COUNT] = अणु
	/* SaffirePro 10 */
	[0] = अणु
		[SAFFIREPRO_CLOCK_SOURCE_INTERNAL]  =  0,
		[SAFFIREPRO_CLOCK_SOURCE_SKIP]      = -1, /* not supported */
		[SAFFIREPRO_CLOCK_SOURCE_SPDIF]     =  1,
		[SAFFIREPRO_CLOCK_SOURCE_ADAT1]     = -1, /* not supported */
		[SAFFIREPRO_CLOCK_SOURCE_ADAT2]     = -1, /* not supported */
		[SAFFIREPRO_CLOCK_SOURCE_WORDCLOCK] =  2,
	पूर्ण,
	/* SaffirePro 26 */
	[1] = अणु
		[SAFFIREPRO_CLOCK_SOURCE_INTERNAL]  =  0,
		[SAFFIREPRO_CLOCK_SOURCE_SKIP]      = -1, /* not supported */
		[SAFFIREPRO_CLOCK_SOURCE_SPDIF]     =  1,
		[SAFFIREPRO_CLOCK_SOURCE_ADAT1]     =  2,
		[SAFFIREPRO_CLOCK_SOURCE_ADAT2]     =  3,
		[SAFFIREPRO_CLOCK_SOURCE_WORDCLOCK] =  4,
	पूर्ण
पूर्ण;

अटल पूर्णांक
saffirepro_both_clk_freq_get(काष्ठा snd_bebob *bebob, अचिन्हित पूर्णांक *rate)
अणु
	u32 id;
	पूर्णांक err;

	err = saffire_पढ़ो_quad(bebob, SAFFIREPRO_RATE_NOREBOOT, &id);
	अगर (err < 0)
		जाओ end;
	अगर (id >= ARRAY_SIZE(rates))
		err = -EIO;
	अन्यथा
		*rate = rates[id];
end:
	वापस err;
पूर्ण
अटल पूर्णांक
saffirepro_both_clk_freq_set(काष्ठा snd_bebob *bebob, अचिन्हित पूर्णांक rate)
अणु
	u32 id;

	क्रम (id = 0; id < ARRAY_SIZE(rates); id++) अणु
		अगर (rates[id] == rate)
			अवरोध;
	पूर्ण
	अगर (id == ARRAY_SIZE(rates))
		वापस -EINVAL;

	वापस saffire_ग_लिखो_quad(bebob, SAFFIREPRO_RATE_NOREBOOT, id);
पूर्ण

/*
 * query hardware क्रम current घड़ी source, वापस our पूर्णांकernally
 * used घड़ी index in *id, depending on hardware.
 */
अटल पूर्णांक
saffirepro_both_clk_src_get(काष्ठा snd_bebob *bebob, अचिन्हित पूर्णांक *id)
अणु
	पूर्णांक err;
	u32 value;       /* घड़ी source पढ़ो from hw रेजिस्टर */
	स्थिर चिन्हित अक्षर *map;

	err = saffire_पढ़ो_quad(bebob, SAFFIREPRO_OFFSET_CLOCK_SOURCE, &value);
	अगर (err < 0)
		जाओ end;

	/* depending on hardware, use a dअगरferent mapping */
	अगर (bebob->spec->घड़ी->types == saffirepro_10_clk_src_types)
		map = saffirepro_clk_maps[0];
	अन्यथा
		map = saffirepro_clk_maps[1];

	/* In a हाल that this driver cannot handle the value of रेजिस्टर. */
	value &= SAFFIREPRO_CLOCK_SOURCE_SELECT_MASK;
	अगर (value >= SAFFIREPRO_CLOCK_SOURCE_COUNT || map[value] < 0) अणु
		err = -EIO;
		जाओ end;
	पूर्ण

	*id = (अचिन्हित पूर्णांक)map[value];
end:
	वापस err;
पूर्ण

स्थिर काष्ठा snd_bebob_spec saffire_le_spec;
अटल स्थिर क्रमागत snd_bebob_घड़ी_प्रकारype saffire_both_clk_src_types[] = अणु
	SND_BEBOB_CLOCK_TYPE_INTERNAL,
	SND_BEBOB_CLOCK_TYPE_EXTERNAL,
पूर्ण;
अटल पूर्णांक
saffire_both_clk_src_get(काष्ठा snd_bebob *bebob, अचिन्हित पूर्णांक *id)
अणु
	पूर्णांक err;
	u32 value;

	err = saffire_पढ़ो_quad(bebob, SAFFIRE_OFFSET_CLOCK_SOURCE, &value);
	अगर (err >= 0)
		*id = 0xff & value;

	वापस err;
पूर्ण;
अटल स्थिर अक्षर *स्थिर saffire_le_meter_labels[] = अणु
	ANA_IN, ANA_IN, DIG_IN,
	ANA_OUT, ANA_OUT, ANA_OUT, ANA_OUT,
	STM_IN, STM_IN
पूर्ण;
अटल स्थिर अक्षर *स्थिर saffire_meter_labels[] = अणु
	ANA_IN, ANA_IN,
	STM_IN, STM_IN, STM_IN, STM_IN, STM_IN,
पूर्ण;
अटल पूर्णांक
saffire_meter_get(काष्ठा snd_bebob *bebob, u32 *buf, अचिन्हित पूर्णांक size)
अणु
	स्थिर काष्ठा snd_bebob_meter_spec *spec = bebob->spec->meter;
	अचिन्हित पूर्णांक channels;
	u64 offset;
	पूर्णांक err;

	अगर (spec->labels == saffire_le_meter_labels)
		offset = SAFFIRE_LE_OFFSET_METER;
	अन्यथा
		offset = SAFFIRE_OFFSET_METER;

	channels = spec->num * 2;
	अगर (size < channels * माप(u32))
		वापस -EIO;

	err = saffire_पढ़ो_block(bebob, offset, buf, size);
	अगर (err >= 0 && spec->labels == saffire_le_meter_labels) अणु
		swap(buf[1], buf[3]);
		swap(buf[2], buf[3]);
		swap(buf[3], buf[4]);

		swap(buf[7], buf[10]);
		swap(buf[8], buf[10]);
		swap(buf[9], buf[11]);
		swap(buf[11], buf[12]);

		swap(buf[15], buf[16]);
	पूर्ण

	वापस err;
पूर्ण

अटल स्थिर काष्ठा snd_bebob_rate_spec saffirepro_both_rate_spec = अणु
	.get	= &saffirepro_both_clk_freq_get,
	.set	= &saffirepro_both_clk_freq_set,
पूर्ण;
/* Saffire Pro 26 I/O  */
अटल स्थिर काष्ठा snd_bebob_घड़ी_spec saffirepro_26_clk_spec = अणु
	.num	= ARRAY_SIZE(saffirepro_26_clk_src_types),
	.types	= saffirepro_26_clk_src_types,
	.get	= &saffirepro_both_clk_src_get,
पूर्ण;
स्थिर काष्ठा snd_bebob_spec saffirepro_26_spec = अणु
	.घड़ी	= &saffirepro_26_clk_spec,
	.rate	= &saffirepro_both_rate_spec,
	.meter	= शून्य
पूर्ण;
/* Saffire Pro 10 I/O */
अटल स्थिर काष्ठा snd_bebob_घड़ी_spec saffirepro_10_clk_spec = अणु
	.num	= ARRAY_SIZE(saffirepro_10_clk_src_types),
	.types	= saffirepro_10_clk_src_types,
	.get	= &saffirepro_both_clk_src_get,
पूर्ण;
स्थिर काष्ठा snd_bebob_spec saffirepro_10_spec = अणु
	.घड़ी	= &saffirepro_10_clk_spec,
	.rate	= &saffirepro_both_rate_spec,
	.meter	= शून्य
पूर्ण;

अटल स्थिर काष्ठा snd_bebob_rate_spec saffire_both_rate_spec = अणु
	.get	= &snd_bebob_stream_get_rate,
	.set	= &snd_bebob_stream_set_rate,
पूर्ण;
अटल स्थिर काष्ठा snd_bebob_घड़ी_spec saffire_both_clk_spec = अणु
	.num	= ARRAY_SIZE(saffire_both_clk_src_types),
	.types	= saffire_both_clk_src_types,
	.get	= &saffire_both_clk_src_get,
पूर्ण;
/* Saffire LE */
अटल स्थिर काष्ठा snd_bebob_meter_spec saffire_le_meter_spec = अणु
	.num	= ARRAY_SIZE(saffire_le_meter_labels),
	.labels	= saffire_le_meter_labels,
	.get	= &saffire_meter_get,
पूर्ण;
स्थिर काष्ठा snd_bebob_spec saffire_le_spec = अणु
	.घड़ी	= &saffire_both_clk_spec,
	.rate	= &saffire_both_rate_spec,
	.meter	= &saffire_le_meter_spec
पूर्ण;
/* Saffire */
अटल स्थिर काष्ठा snd_bebob_meter_spec saffire_meter_spec = अणु
	.num	= ARRAY_SIZE(saffire_meter_labels),
	.labels	= saffire_meter_labels,
	.get	= &saffire_meter_get,
पूर्ण;
स्थिर काष्ठा snd_bebob_spec saffire_spec = अणु
	.घड़ी	= &saffire_both_clk_spec,
	.rate	= &saffire_both_rate_spec,
	.meter	= &saffire_meter_spec
पूर्ण;
