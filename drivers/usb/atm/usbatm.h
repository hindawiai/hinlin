<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/******************************************************************************
 *  usbaपंचांग.h - Generic USB xDSL driver core
 *
 *  Copyright (C) 2001, Alcatel
 *  Copyright (C) 2003, Duncan Sands, SolNegro, Josep Comas
 *  Copyright (C) 2004, David Woodhouse
 ******************************************************************************/

#अगर_अघोषित	_USBATM_H_
#घोषणा	_USBATM_H_

#समावेश <linux/aपंचांग.h>
#समावेश <linux/aपंचांगdev.h>
#समावेश <linux/completion.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kref.h>
#समावेश <linux/list.h>
#समावेश <linux/stringअगरy.h>
#समावेश <linux/usb.h>
#समावेश <linux/mutex.h>
#समावेश <linux/ratelimit.h>

/*
#घोषणा VERBOSE_DEBUG
*/

#घोषणा usb_err(instance, क्रमmat, arg...)	\
	dev_err(&(instance)->usb_पूर्णांकf->dev , क्रमmat , ## arg)
#घोषणा usb_info(instance, क्रमmat, arg...)	\
	dev_info(&(instance)->usb_पूर्णांकf->dev , क्रमmat , ## arg)
#घोषणा usb_warn(instance, क्रमmat, arg...)	\
	dev_warn(&(instance)->usb_पूर्णांकf->dev , क्रमmat , ## arg)
#घोषणा usb_dbg(instance, क्रमmat, arg...)	\
	dev_dbg(&(instance)->usb_पूर्णांकf->dev , क्रमmat , ## arg)

/* FIXME: move to dev_* once ATM is driver model aware */
#घोषणा aपंचांग_prपूर्णांकk(level, instance, क्रमmat, arg...)	\
	prपूर्णांकk(level "ATM dev %d: " क्रमmat ,		\
	(instance)->aपंचांग_dev->number , ## arg)

#घोषणा aपंचांग_err(instance, क्रमmat, arg...)	\
	aपंचांग_prपूर्णांकk(KERN_ERR, instance , क्रमmat , ## arg)
#घोषणा aपंचांग_info(instance, क्रमmat, arg...)	\
	aपंचांग_prपूर्णांकk(KERN_INFO, instance , क्रमmat , ## arg)
#घोषणा aपंचांग_warn(instance, क्रमmat, arg...)	\
	aपंचांग_prपूर्णांकk(KERN_WARNING, instance , क्रमmat , ## arg)
#घोषणा aपंचांग_dbg(instance, क्रमmat, ...)					\
	pr_debug("ATM dev %d: " क्रमmat,					\
		 (instance)->aपंचांग_dev->number, ##__VA_ARGS__)
#घोषणा aपंचांग_rldbg(instance, क्रमmat, ...)				\
	pr_debug_ratelimited("ATM dev %d: " क्रमmat,			\
			     (instance)->aपंचांग_dev->number, ##__VA_ARGS__)

/* flags, set by mini-driver in bind() */

#घोषणा UDSL_SKIP_HEAVY_INIT	(1<<0)
#घोषणा UDSL_USE_ISOC		(1<<1)
#घोषणा UDSL_IGNORE_EILSEQ	(1<<2)


/* mini driver */

काष्ठा usbaपंचांग_data;

/*
*  Assuming all methods exist and succeed, they are called in this order:
*
*	bind, heavy_init, aपंचांग_start, ..., aपंचांग_stop, unbind
*/

काष्ठा usbaपंचांग_driver अणु
	स्थिर अक्षर *driver_name;

	/* init device ... can sleep, or cause probe() failure */
	पूर्णांक (*bind) (काष्ठा usbaपंचांग_data *, काष्ठा usb_पूर्णांकerface *,
		     स्थिर काष्ठा usb_device_id *id);

	/* additional device initialization that is too slow to be करोne in probe() */
	पूर्णांक (*heavy_init) (काष्ठा usbaपंचांग_data *, काष्ठा usb_पूर्णांकerface *);

	/* cleanup device ... can sleep, but can't fail */
	व्योम (*unbind) (काष्ठा usbaपंचांग_data *, काष्ठा usb_पूर्णांकerface *);

	/* init ATM device ... can sleep, or cause ATM initialization failure */
	पूर्णांक (*aपंचांग_start) (काष्ठा usbaपंचांग_data *, काष्ठा aपंचांग_dev *);

	/* cleanup ATM device ... can sleep, but can't fail */
	व्योम (*aपंचांग_stop) (काष्ठा usbaपंचांग_data *, काष्ठा aपंचांग_dev *);

	पूर्णांक bulk_in;	/* bulk rx endpoपूर्णांक */
	पूर्णांक isoc_in;	/* isochronous rx endpoपूर्णांक */
	पूर्णांक bulk_out;	/* bulk tx endpoपूर्णांक */

	अचिन्हित rx_padding;
	अचिन्हित tx_padding;
पूर्ण;

बाह्य पूर्णांक usbaपंचांग_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf, स्थिर काष्ठा usb_device_id *id,
		काष्ठा usbaपंचांग_driver *driver);
बाह्य व्योम usbaपंचांग_usb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf);


काष्ठा usbaपंचांग_channel अणु
	पूर्णांक endpoपूर्णांक;			/* usb pipe */
	अचिन्हित पूर्णांक stride;		/* ATM cell size + padding */
	अचिन्हित पूर्णांक buf_size;		/* urb buffer size */
	अचिन्हित पूर्णांक packet_size;	/* endpoपूर्णांक maxpacket */
	spinlock_t lock;
	काष्ठा list_head list;
	काष्ठा tasklet_काष्ठा tasklet;
	काष्ठा समयr_list delay;
	काष्ठा usbaपंचांग_data *usbaपंचांग;
पूर्ण;

/* मुख्य driver data */

काष्ठा usbaपंचांग_data अणु
	/******************
	*  खुला fields  *
	******************/

	/* mini driver */
	काष्ठा usbaपंचांग_driver *driver;
	व्योम *driver_data;
	अक्षर driver_name[16];
	अचिन्हित पूर्णांक flags; /* set by mini-driver in bind() */

	/* USB device */
	काष्ठा usb_device *usb_dev;
	काष्ठा usb_पूर्णांकerface *usb_पूर्णांकf;
	अक्षर description[64];

	/* ATM device */
	काष्ठा aपंचांग_dev *aपंचांग_dev;

	/********************************
	*  निजी fields - करो not use  *
	********************************/

	काष्ठा kref refcount;
	काष्ठा mutex serialize;
	पूर्णांक disconnected;

	/* heavy init */
	काष्ठा task_काष्ठा *thपढ़ो;
	काष्ठा completion thपढ़ो_started;
	काष्ठा completion thपढ़ो_निकासed;

	/* ATM device */
	काष्ठा list_head vcc_list;

	काष्ठा usbaपंचांग_channel rx_channel;
	काष्ठा usbaपंचांग_channel tx_channel;

	काष्ठा sk_buff_head sndqueue;
	काष्ठा sk_buff *current_skb;	/* being emptied */

	काष्ठा usbaपंचांग_vcc_data *cached_vcc;
	पूर्णांक cached_vci;
	लघु cached_vpi;

	अचिन्हित अक्षर *cell_buf;	/* holds partial rx cell */
	अचिन्हित पूर्णांक buf_usage;

	काष्ठा urb *urbs[];
पूर्ण;

अटल अंतरभूत व्योम *to_usbaपंचांग_driver_data(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usbaपंचांग_data *usbaपंचांग_instance;

	अगर (पूर्णांकf == शून्य)
		वापस शून्य;

	usbaपंचांग_instance = usb_get_पूर्णांकfdata(पूर्णांकf);

	अगर (usbaपंचांग_instance == शून्य) /* set शून्य beक्रमe unbind() */
		वापस शून्य;

	वापस usbaपंचांग_instance->driver_data; /* set शून्य after unbind() */
पूर्ण

#पूर्ण_अगर	/* _USBATM_H_ */
