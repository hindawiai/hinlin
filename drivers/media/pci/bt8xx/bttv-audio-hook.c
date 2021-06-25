<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Handlers क्रम board audio hooks, split from bttv-cards
 *
 * Copyright (c) 2006 Mauro Carvalho Chehab <mchehab@kernel.org>
 */

#समावेश "bttv-audio-hook.h"

#समावेश <linux/delay.h>

/* ----------------------------------------------------------------------- */
/* winview                                                                 */

व्योम winview_volume(काष्ठा bttv *btv, __u16 volume)
अणु
	/* PT2254A programming Jon Tombs, jon@gte.esi.us.es */
	पूर्णांक bits_out, loops, vol, data;

	/* 32 levels logarithmic */
	vol = 32 - ((volume>>11));
	/* units */
	bits_out = (PT2254_DBS_IN_2>>(vol%5));
	/* tens */
	bits_out |= (PT2254_DBS_IN_10>>(vol/5));
	bits_out |= PT2254_L_CHANNEL | PT2254_R_CHANNEL;
	data = gpio_पढ़ो();
	data &= ~(WINVIEW_PT2254_CLK| WINVIEW_PT2254_DATA|
		  WINVIEW_PT2254_STROBE);
	क्रम (loops = 17; loops >= 0 ; loops--) अणु
		अगर (bits_out & (1<<loops))
			data |=  WINVIEW_PT2254_DATA;
		अन्यथा
			data &= ~WINVIEW_PT2254_DATA;
		gpio_ग_लिखो(data);
		udelay(5);
		data |= WINVIEW_PT2254_CLK;
		gpio_ग_लिखो(data);
		udelay(5);
		data &= ~WINVIEW_PT2254_CLK;
		gpio_ग_लिखो(data);
	पूर्ण
	data |=  WINVIEW_PT2254_STROBE;
	data &= ~WINVIEW_PT2254_DATA;
	gpio_ग_लिखो(data);
	udelay(10);
	data &= ~WINVIEW_PT2254_STROBE;
	gpio_ग_लिखो(data);
पूर्ण

/* ----------------------------------------------------------------------- */
/* mono/stereo control क्रम various cards (which करोn't use i2c chips but    */
/* connect something to the GPIO pins                                      */

व्योम gvbctv3pci_audio(काष्ठा bttv *btv, काष्ठा v4l2_tuner *t, पूर्णांक set)
अणु
	अचिन्हित पूर्णांक con;

	अगर (!set) अणु
		/* Not much to करो here */
		t->audmode = V4L2_TUNER_MODE_LANG1;
		t->rxsubchans = V4L2_TUNER_SUB_MONO |
				V4L2_TUNER_SUB_STEREO |
				V4L2_TUNER_SUB_LANG1 |
				V4L2_TUNER_SUB_LANG2;

		वापस;
	पूर्ण

	gpio_inout(0x300, 0x300);
	चयन (t->audmode) अणु
	हाल V4L2_TUNER_MODE_LANG1:
	शेष:
		con = 0x000;
		अवरोध;
	हाल V4L2_TUNER_MODE_LANG2:
		con = 0x300;
		अवरोध;
	हाल V4L2_TUNER_MODE_STEREO:
		con = 0x200;
		अवरोध;
	पूर्ण
	gpio_bits(0x300, con);
पूर्ण

व्योम gvbctv5pci_audio(काष्ठा bttv *btv, काष्ठा v4l2_tuner *t, पूर्णांक set)
अणु
	अचिन्हित पूर्णांक val, con;

	अगर (btv->radio_user)
		वापस;

	val = gpio_पढ़ो();
	अगर (set) अणु
		चयन (t->audmode) अणु
		हाल V4L2_TUNER_MODE_LANG2:
			con = 0x300;
			अवरोध;
		हाल V4L2_TUNER_MODE_LANG1_LANG2:
			con = 0x100;
			अवरोध;
		शेष:
			con = 0x000;
			अवरोध;
		पूर्ण
		अगर (con != (val & 0x300)) अणु
			gpio_bits(0x300, con);
			अगर (bttv_gpio)
				bttv_gpio_tracking(btv, "gvbctv5pci");
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (val & 0x70) अणु
		  हाल 0x10:
			t->rxsubchans = V4L2_TUNER_SUB_LANG1 |  V4L2_TUNER_SUB_LANG2;
			t->audmode = V4L2_TUNER_MODE_LANG1_LANG2;
			अवरोध;
		  हाल 0x30:
			t->rxsubchans = V4L2_TUNER_SUB_LANG2;
			t->audmode = V4L2_TUNER_MODE_LANG1_LANG2;
			अवरोध;
		  हाल 0x50:
			t->rxsubchans = V4L2_TUNER_SUB_LANG1;
			t->audmode = V4L2_TUNER_MODE_LANG1_LANG2;
			अवरोध;
		  हाल 0x60:
			t->rxsubchans = V4L2_TUNER_SUB_STEREO;
			t->audmode = V4L2_TUNER_MODE_STEREO;
			अवरोध;
		  हाल 0x70:
			t->rxsubchans = V4L2_TUNER_SUB_MONO;
			t->audmode = V4L2_TUNER_MODE_MONO;
			अवरोध;
		  शेष:
			t->rxsubchans = V4L2_TUNER_SUB_MONO |
					 V4L2_TUNER_SUB_STEREO |
					 V4L2_TUNER_SUB_LANG1 |
					 V4L2_TUNER_SUB_LANG2;
			t->audmode = V4L2_TUNER_MODE_LANG1;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Mario Medina Nussbaum <medisoft@alohabbs.org.mx>
 *  I discover that on BT848_GPIO_DATA address a byte 0xcce enable stereo,
 *  0xdde enables mono and 0xccd enables sap
 *
 * Petr Vandrovec <VANDROVE@vc.cvut.cz>
 *  P.S.: At least mask in line above is wrong - GPIO pins 3,2 select
 *  input/output sound connection, so both must be set क्रम output mode.
 *
 * Looks like it's needed only क्रम the "tvphone", the "tvphone 98"
 * handles this with a tda9840
 *
 */

व्योम avermedia_tvphone_audio(काष्ठा bttv *btv, काष्ठा v4l2_tuner *t, पूर्णांक set)
अणु
	पूर्णांक val;

	अगर (!set) अणु
		/* Not much to करो here */
		t->audmode = V4L2_TUNER_MODE_LANG1;
		t->rxsubchans = V4L2_TUNER_SUB_MONO |
				V4L2_TUNER_SUB_STEREO |
				V4L2_TUNER_SUB_LANG1 |
				V4L2_TUNER_SUB_LANG2;

		वापस;
	पूर्ण

	चयन (t->audmode) अणु
	हाल V4L2_TUNER_MODE_LANG2:   /* SAP */
		val = 0x02;
		अवरोध;
	हाल V4L2_TUNER_MODE_STEREO:
		val = 0x01;
		अवरोध;
	शेष:
		वापस;
	पूर्ण
	gpio_bits(0x03, val);
	अगर (bttv_gpio)
		bttv_gpio_tracking(btv, "avermedia");
पूर्ण


व्योम avermedia_tv_stereo_audio(काष्ठा bttv *btv, काष्ठा v4l2_tuner *t, पूर्णांक set)
अणु
	पूर्णांक val = 0;

	अगर (!set) अणु
		/* Not much to करो here */
		t->audmode = V4L2_TUNER_MODE_LANG1;
		t->rxsubchans = V4L2_TUNER_SUB_MONO |
				V4L2_TUNER_SUB_STEREO |
				V4L2_TUNER_SUB_LANG1 |
				V4L2_TUNER_SUB_LANG2;

		वापस;
	पूर्ण

	चयन (t->audmode) अणु
	हाल V4L2_TUNER_MODE_LANG2:   /* SAP */
		val = 0x01;
		अवरोध;
	हाल V4L2_TUNER_MODE_STEREO:
		val = 0x02;
		अवरोध;
	शेष:
		val = 0;
		अवरोध;
	पूर्ण
	btaor(val, ~0x03, BT848_GPIO_DATA);
	अगर (bttv_gpio)
		bttv_gpio_tracking(btv, "avermedia");
पूर्ण

/* Lअगरetec 9415 handling */

व्योम lt9415_audio(काष्ठा bttv *btv, काष्ठा v4l2_tuner *t, पूर्णांक set)
अणु
	पूर्णांक val = 0;

	अगर (gpio_पढ़ो() & 0x4000) अणु
		t->audmode = V4L2_TUNER_MODE_MONO;
		वापस;
	पूर्ण

	अगर (!set) अणु
		/* Not much to करो here */
		t->audmode = V4L2_TUNER_MODE_LANG1;
		t->rxsubchans = V4L2_TUNER_SUB_MONO |
				V4L2_TUNER_SUB_STEREO |
				V4L2_TUNER_SUB_LANG1 |
				V4L2_TUNER_SUB_LANG2;

		वापस;
	पूर्ण

	चयन (t->audmode) अणु
	हाल V4L2_TUNER_MODE_LANG2:	/* A2 SAP */
		val = 0x0080;
		अवरोध;
	हाल V4L2_TUNER_MODE_STEREO:	/* A2 stereo */
		val = 0x0880;
		अवरोध;
	शेष:
		val = 0;
		अवरोध;
	पूर्ण

	gpio_bits(0x0880, val);
	अगर (bttv_gpio)
		bttv_gpio_tracking(btv, "lt9415");
पूर्ण

/* TDA9821 on TerraTV+ Bt848, Bt878 */
व्योम terratv_audio(काष्ठा bttv *btv,  काष्ठा v4l2_tuner *t, पूर्णांक set)
अणु
	अचिन्हित पूर्णांक con = 0;

	अगर (!set) अणु
		/* Not much to करो here */
		t->audmode = V4L2_TUNER_MODE_LANG1;
		t->rxsubchans = V4L2_TUNER_SUB_MONO |
				V4L2_TUNER_SUB_STEREO |
				V4L2_TUNER_SUB_LANG1 |
				V4L2_TUNER_SUB_LANG2;

		वापस;
	पूर्ण

	gpio_inout(0x180000, 0x180000);
	चयन (t->audmode) अणु
	हाल V4L2_TUNER_MODE_LANG2:
		con = 0x080000;
		अवरोध;
	हाल V4L2_TUNER_MODE_STEREO:
		con = 0x180000;
		अवरोध;
	शेष:
		con = 0;
		अवरोध;
	पूर्ण
	gpio_bits(0x180000, con);
	अगर (bttv_gpio)
		bttv_gpio_tracking(btv, "terratv");
पूर्ण


व्योम winfast2000_audio(काष्ठा bttv *btv, काष्ठा v4l2_tuner *t, पूर्णांक set)
अणु
	अचिन्हित दीर्घ val;

	अगर (!set) अणु
		/* Not much to करो here */
		t->audmode = V4L2_TUNER_MODE_LANG1;
		t->rxsubchans = V4L2_TUNER_SUB_MONO |
				V4L2_TUNER_SUB_STEREO |
				V4L2_TUNER_SUB_LANG1 |
				V4L2_TUNER_SUB_LANG2;

		वापस;
	पूर्ण

	/*btor (0xc32000, BT848_GPIO_OUT_EN);*/
	चयन (t->audmode) अणु
	हाल V4L2_TUNER_MODE_MONO:
	हाल V4L2_TUNER_MODE_LANG1:
		val = 0x420000;
		अवरोध;
	हाल V4L2_TUNER_MODE_LANG2: /* SAP */
		val = 0x410000;
		अवरोध;
	हाल V4L2_TUNER_MODE_STEREO:
		val = 0x020000;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	gpio_bits(0x430000, val);
	अगर (bttv_gpio)
		bttv_gpio_tracking(btv, "winfast2000");
पूर्ण

/*
 * Dariusz Kowalewski <darekk@स्वतःmex.pl>
 * sound control क्रम Prolink PV-BT878P+9B (PixelView PlayTV Pro FM+NICAM
 * revision 9B has on-board TDA9874A sound decoder).
 *
 * Note: There are card variants without tda9874a. Forcing the "stereo sound route"
 *       will mute this cards.
 */
व्योम pvbt878p9b_audio(काष्ठा bttv *btv, काष्ठा v4l2_tuner *t, पूर्णांक set)
अणु
	अचिन्हित पूर्णांक val = 0;

	अगर (btv->radio_user)
		वापस;

	अगर (!set) अणु
		/* Not much to करो here */
		t->audmode = V4L2_TUNER_MODE_LANG1;
		t->rxsubchans = V4L2_TUNER_SUB_MONO |
				V4L2_TUNER_SUB_STEREO |
				V4L2_TUNER_SUB_LANG1 |
				V4L2_TUNER_SUB_LANG2;

		वापस;
	पूर्ण

	चयन (t->audmode) अणु
	हाल V4L2_TUNER_MODE_MONO:
		val = 0x01;
		अवरोध;
	हाल V4L2_TUNER_MODE_LANG1:
	हाल V4L2_TUNER_MODE_LANG2:
	हाल V4L2_TUNER_MODE_STEREO:
		val = 0x02;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	gpio_bits(0x03, val);
	अगर (bttv_gpio)
		bttv_gpio_tracking(btv, "pvbt878p9b");
पूर्ण

/*
 * Dariusz Kowalewski <darekk@स्वतःmex.pl>
 * sound control क्रम FlyVideo 2000S (with tda9874 decoder)
 * based on pvbt878p9b_audio() - this is not tested, please fix!!!
 */
व्योम fv2000s_audio(काष्ठा bttv *btv, काष्ठा v4l2_tuner *t, पूर्णांक set)
अणु
	अचिन्हित पूर्णांक val;

	अगर (btv->radio_user)
		वापस;

	अगर (!set) अणु
		/* Not much to करो here */
		t->audmode = V4L2_TUNER_MODE_LANG1;
		t->rxsubchans = V4L2_TUNER_SUB_MONO |
				V4L2_TUNER_SUB_STEREO |
				V4L2_TUNER_SUB_LANG1 |
				V4L2_TUNER_SUB_LANG2;

		वापस;
	पूर्ण

	चयन (t->audmode) अणु
	हाल V4L2_TUNER_MODE_MONO:
		val = 0x0000;
		अवरोध;
	हाल V4L2_TUNER_MODE_LANG1:
	हाल V4L2_TUNER_MODE_LANG2:
	हाल V4L2_TUNER_MODE_STEREO:
		val = 0x1080; /*-dk-???: 0x0880, 0x0080, 0x1800 ... */
		अवरोध;
	शेष:
		वापस;
	पूर्ण
	gpio_bits(0x1800, val);
	अगर (bttv_gpio)
		bttv_gpio_tracking(btv, "fv2000s");
पूर्ण

/*
 * sound control क्रम Canopus WinDVR PCI
 * Masaki Suzuki <masaki@btree.org>
 */
व्योम windvr_audio(काष्ठा bttv *btv, काष्ठा v4l2_tuner *t, पूर्णांक set)
अणु
	अचिन्हित दीर्घ val;

	अगर (!set) अणु
		/* Not much to करो here */
		t->audmode = V4L2_TUNER_MODE_LANG1;
		t->rxsubchans = V4L2_TUNER_SUB_MONO |
				V4L2_TUNER_SUB_STEREO |
				V4L2_TUNER_SUB_LANG1 |
				V4L2_TUNER_SUB_LANG2;

		वापस;
	पूर्ण

	चयन (t->audmode) अणु
	हाल V4L2_TUNER_MODE_MONO:
		val = 0x040000;
		अवरोध;
	हाल V4L2_TUNER_MODE_LANG2:
		val = 0x100000;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	gpio_bits(0x140000, val);
	अगर (bttv_gpio)
		bttv_gpio_tracking(btv, "windvr");
पूर्ण

/*
 * sound control क्रम AD-TVK503
 * Hiroshi Takekawa <sian@big.or.jp>
 */
व्योम adtvk503_audio(काष्ठा bttv *btv, काष्ठा v4l2_tuner *t, पूर्णांक set)
अणु
	अचिन्हित पूर्णांक con = 0xffffff;

	/* btaor(0x1e0000, ~0x1e0000, BT848_GPIO_OUT_EN); */

	अगर (!set) अणु
		/* Not much to करो here */
		t->audmode = V4L2_TUNER_MODE_LANG1;
		t->rxsubchans = V4L2_TUNER_SUB_MONO |
				V4L2_TUNER_SUB_STEREO |
				V4L2_TUNER_SUB_LANG1 |
				V4L2_TUNER_SUB_LANG2;

		वापस;
	पूर्ण

	/* btor(***, BT848_GPIO_OUT_EN); */
	चयन (t->audmode) अणु
	हाल V4L2_TUNER_MODE_LANG1:
		con = 0x00000000;
		अवरोध;
	हाल V4L2_TUNER_MODE_LANG2:
		con = 0x00180000;
		अवरोध;
	हाल V4L2_TUNER_MODE_STEREO:
		con = 0x00000000;
		अवरोध;
	हाल V4L2_TUNER_MODE_MONO:
		con = 0x00060000;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	gpio_bits(0x1e0000, con);
	अगर (bttv_gpio)
		bttv_gpio_tracking(btv, "adtvk503");
पूर्ण
