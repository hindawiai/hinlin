<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Zoran zr36057/zr36067 PCI controller driver, क्रम the
 * Pinnacle/Miro DC10/DC10+/DC30/DC30+, Iomega Buz, Linux
 * Media Lअसल LML33/LML33R10.
 *
 * This part handles card-specअगरic data and detection
 *
 * Copyright (C) 2000 Serguei Miriकरोnov <mirsev@cicese.mx>
 */

#अगर_अघोषित __ZORAN_DEVICE_H__
#घोषणा __ZORAN_DEVICE_H__

/* general purpose I/O */
बाह्य व्योम GPIO(काष्ठा zoran *zr, पूर्णांक bit, अचिन्हित पूर्णांक value);

/* codec (or actually: guest bus) access */
बाह्य पूर्णांक post_office_रुको(काष्ठा zoran *zr);
बाह्य पूर्णांक post_office_ग_लिखो(काष्ठा zoran *zr, अचिन्हित पूर्णांक guest, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक value);
बाह्य पूर्णांक post_office_पढ़ो(काष्ठा zoran *zr, अचिन्हित पूर्णांक guest, अचिन्हित पूर्णांक reg);

बाह्य व्योम detect_guest_activity(काष्ठा zoran *zr);

बाह्य व्योम jpeg_codec_sleep(काष्ठा zoran *zr, पूर्णांक sleep);
बाह्य पूर्णांक jpeg_codec_reset(काष्ठा zoran *zr);

/* zr360x7 access to raw capture */
बाह्य व्योम zr36057_overlay(काष्ठा zoran *zr, पूर्णांक on);
बाह्य व्योम ग_लिखो_overlay_mask(काष्ठा zoran_fh *fh, काष्ठा v4l2_clip *vp, पूर्णांक count);
बाह्य व्योम zr36057_set_memgrab(काष्ठा zoran *zr, पूर्णांक mode);
बाह्य पूर्णांक रुको_grab_pending(काष्ठा zoran *zr);

/* पूर्णांकerrupts */
बाह्य व्योम prपूर्णांक_पूर्णांकerrupts(काष्ठा zoran *zr);
बाह्य व्योम clear_पूर्णांकerrupt_counters(काष्ठा zoran *zr);
बाह्य irqवापस_t zoran_irq(पूर्णांक irq, व्योम *dev_id);

/* JPEG codec access */
बाह्य व्योम jpeg_start(काष्ठा zoran *zr);
बाह्य व्योम zr36057_enable_jpg(काष्ठा zoran *zr,
			       क्रमागत zoran_codec_mode mode);
बाह्य व्योम zoran_feed_stat_com(काष्ठा zoran *zr);

/* general */
बाह्य व्योम zoran_set_pci_master(काष्ठा zoran *zr, पूर्णांक set_master);
बाह्य व्योम zoran_init_hardware(काष्ठा zoran *zr);
बाह्य व्योम zr36057_restart(काष्ठा zoran *zr);

बाह्य स्थिर काष्ठा zoran_क्रमmat zoran_क्रमmats[];

बाह्य पूर्णांक v4l_nbufs;
बाह्य पूर्णांक v4l_bufsize;
बाह्य पूर्णांक jpg_nbufs;
बाह्य पूर्णांक jpg_bufsize;
बाह्य पूर्णांक pass_through;

/* i2c */
#घोषणा decoder_call(zr, o, f, args...) \
	v4l2_subdev_call(zr->decoder, o, f, ##args)
#घोषणा encoder_call(zr, o, f, args...) \
	v4l2_subdev_call(zr->encoder, o, f, ##args)

#पूर्ण_अगर				/* __ZORAN_DEVICE_H__ */
