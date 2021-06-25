<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   ALSA driver क्रम ICEnsemble ICE1712 (Envy24)
 *
 *   AK4524 / AK4528 / AK4529 / AK4355 / AK4381 पूर्णांकerface
 *
 *	Copyright (c) 2000 Jaroslav Kysela <perex@perex.cz>
 */      

#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश "ice1712.h"

MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>");
MODULE_DESCRIPTION("ICEnsemble ICE17xx <-> AK4xxx AD/DA chip interface");
MODULE_LICENSE("GPL");

अटल व्योम snd_ice1712_akm4xxx_lock(काष्ठा snd_akm4xxx *ak, पूर्णांक chip)
अणु
	काष्ठा snd_ice1712 *ice = ak->निजी_data[0];

	snd_ice1712_save_gpio_status(ice);
पूर्ण

अटल व्योम snd_ice1712_akm4xxx_unlock(काष्ठा snd_akm4xxx *ak, पूर्णांक chip)
अणु
	काष्ठा snd_ice1712 *ice = ak->निजी_data[0];

	snd_ice1712_restore_gpio_status(ice);
पूर्ण

/*
 * ग_लिखो AK4xxx रेजिस्टर
 */
अटल व्योम snd_ice1712_akm4xxx_ग_लिखो(काष्ठा snd_akm4xxx *ak, पूर्णांक chip,
				      अचिन्हित अक्षर addr, अचिन्हित अक्षर data)
अणु
	अचिन्हित पूर्णांक पंचांगp;
	पूर्णांक idx;
	अचिन्हित पूर्णांक addrdata;
	काष्ठा snd_ak4xxx_निजी *priv = (व्योम *)ak->निजी_value[0];
	काष्ठा snd_ice1712 *ice = ak->निजी_data[0];

	अगर (snd_BUG_ON(chip < 0 || chip >= 4))
		वापस;

	पंचांगp = snd_ice1712_gpio_पढ़ो(ice);
	पंचांगp |= priv->add_flags;
	पंचांगp &= ~priv->mask_flags;
	अगर (priv->cs_mask == priv->cs_addr) अणु
		अगर (priv->cअगर) अणु
			पंचांगp |= priv->cs_mask; /* start without chip select */
		पूर्ण  अन्यथा अणु
			पंचांगp &= ~priv->cs_mask; /* chip select low */
			snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
			udelay(1);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* करोesn't handle cf=1 yet */
		पंचांगp &= ~priv->cs_mask;
		पंचांगp |= priv->cs_addr;
		snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
		udelay(1);
	पूर्ण

	/* build I2C address + data byte */
	addrdata = (priv->caddr << 6) | 0x20 | (addr & 0x1f);
	addrdata = (addrdata << 8) | data;
	क्रम (idx = 15; idx >= 0; idx--) अणु
		/* drop घड़ी */
		पंचांगp &= ~priv->clk_mask;
		snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
		udelay(1);
		/* set data */
		अगर (addrdata & (1 << idx))
			पंचांगp |= priv->data_mask;
		अन्यथा
			पंचांगp &= ~priv->data_mask;
		snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
		udelay(1);
		/* उठाओ घड़ी */
		पंचांगp |= priv->clk_mask;
		snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
		udelay(1);
	पूर्ण

	अगर (priv->cs_mask == priv->cs_addr) अणु
		अगर (priv->cअगर) अणु
			/* निश्चित a cs pulse to trigger */
			पंचांगp &= ~priv->cs_mask;
			snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
			udelay(1);
		पूर्ण
		पंचांगp |= priv->cs_mask; /* chip select high to trigger */
	पूर्ण अन्यथा अणु
		पंचांगp &= ~priv->cs_mask;
		पंचांगp |= priv->cs_none; /* deselect address */
	पूर्ण
	snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
	udelay(1);
पूर्ण

/*
 * initialize the काष्ठा snd_akm4xxx record with the ढाँचा
 */
पूर्णांक snd_ice1712_akm4xxx_init(काष्ठा snd_akm4xxx *ak, स्थिर काष्ठा snd_akm4xxx *temp,
			     स्थिर काष्ठा snd_ak4xxx_निजी *_priv, काष्ठा snd_ice1712 *ice)
अणु
	काष्ठा snd_ak4xxx_निजी *priv;

	अगर (_priv != शून्य) अणु
		priv = kदो_स्मृति(माप(*priv), GFP_KERNEL);
		अगर (priv == शून्य)
			वापस -ENOMEM;
		*priv = *_priv;
	पूर्ण अन्यथा अणु
		priv = शून्य;
	पूर्ण
	*ak = *temp;
	ak->card = ice->card;
        ak->निजी_value[0] = (अचिन्हित दीर्घ)priv;
	ak->निजी_data[0] = ice;
	अगर (ak->ops.lock == शून्य)
		ak->ops.lock = snd_ice1712_akm4xxx_lock;
	अगर (ak->ops.unlock == शून्य)
		ak->ops.unlock = snd_ice1712_akm4xxx_unlock;
	अगर (ak->ops.ग_लिखो == शून्य)
		ak->ops.ग_लिखो = snd_ice1712_akm4xxx_ग_लिखो;
	snd_akm4xxx_init(ak);
	वापस 0;
पूर्ण

व्योम snd_ice1712_akm4xxx_मुक्त(काष्ठा snd_ice1712 *ice)
अणु
	अचिन्हित पूर्णांक akidx;
	अगर (ice->akm == शून्य)
		वापस;
	क्रम (akidx = 0; akidx < ice->akm_codecs; akidx++) अणु
		काष्ठा snd_akm4xxx *ak = &ice->akm[akidx];
		kमुक्त((व्योम*)ak->निजी_value[0]);
	पूर्ण
	kमुक्त(ice->akm);
पूर्ण

/*
 * build AK4xxx controls
 */
पूर्णांक snd_ice1712_akm4xxx_build_controls(काष्ठा snd_ice1712 *ice)
अणु
	अचिन्हित पूर्णांक akidx;
	पूर्णांक err;

	क्रम (akidx = 0; akidx < ice->akm_codecs; akidx++) अणु
		काष्ठा snd_akm4xxx *ak = &ice->akm[akidx];
		err = snd_akm4xxx_build_controls(ak);
		अगर (err < 0)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

EXPORT_SYMBOL(snd_ice1712_akm4xxx_init);
EXPORT_SYMBOL(snd_ice1712_akm4xxx_मुक्त);
EXPORT_SYMBOL(snd_ice1712_akm4xxx_build_controls);
