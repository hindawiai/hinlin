<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम the media bay on the PowerBook 3400 and 2400.
 *
 * Copyright (C) 1998 Paul Mackerras.
 *
 * Various evolutions by Benjamin Herrenschmidt & Henry Worth
 */
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/sched.h>
#समावेश <linux/समयr.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/init.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/pmac_feature.h>
#समावेश <यंत्र/mediabay.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/ohare.h>
#समावेश <यंत्र/heathrow.h>
#समावेश <यंत्र/keylargo.h>
#समावेश <linux/adb.h>
#समावेश <linux/pmu.h>

#घोषणा MB_FCR32(bay, r)	((bay)->base + ((r) >> 2))
#घोषणा MB_FCR8(bay, r)		(((अस्थिर u8 __iomem *)((bay)->base)) + (r))

#घोषणा MB_IN32(bay,r)		(in_le32(MB_FCR32(bay,r)))
#घोषणा MB_OUT32(bay,r,v)	(out_le32(MB_FCR32(bay,r), (v)))
#घोषणा MB_BIS(bay,r,v)		(MB_OUT32((bay), (r), MB_IN32((bay), r) | (v)))
#घोषणा MB_BIC(bay,r,v)		(MB_OUT32((bay), (r), MB_IN32((bay), r) & ~(v)))
#घोषणा MB_IN8(bay,r)		(in_8(MB_FCR8(bay,r)))
#घोषणा MB_OUT8(bay,r,v)	(out_8(MB_FCR8(bay,r), (v)))

काष्ठा media_bay_info;

काष्ठा mb_ops अणु
	अक्षर*	name;
	व्योम	(*init)(काष्ठा media_bay_info *bay);
	u8	(*content)(काष्ठा media_bay_info *bay);
	व्योम	(*घातer)(काष्ठा media_bay_info *bay, पूर्णांक on_off);
	पूर्णांक	(*setup_bus)(काष्ठा media_bay_info *bay, u8 device_id);
	व्योम	(*un_reset)(काष्ठा media_bay_info *bay);
	व्योम	(*un_reset_ide)(काष्ठा media_bay_info *bay);
पूर्ण;

काष्ठा media_bay_info अणु
	u32 __iomem			*base;
	पूर्णांक				content_id;
	पूर्णांक				state;
	पूर्णांक				last_value;
	पूर्णांक				value_count;
	पूर्णांक				समयr;
	काष्ठा macio_dev		*mdev;
	स्थिर काष्ठा mb_ops*		ops;
	पूर्णांक				index;
	पूर्णांक				cached_gpio;
	पूर्णांक				sleeping;
	पूर्णांक				user_lock;
	काष्ठा mutex			lock;
पूर्ण;

#घोषणा MAX_BAYS	2

अटल काष्ठा media_bay_info media_bays[MAX_BAYS];
अटल पूर्णांक media_bay_count = 0;

/*
 * Wait that number of ms between each step in normal polling mode
 */
#घोषणा MB_POLL_DELAY	25

/*
 * Consider the media-bay ID value stable अगर it is the same क्रम
 * this number of milliseconds
 */
#घोषणा MB_STABLE_DELAY	100

/* Wait after घातering up the media bay this delay in ms
 * समयout bumped क्रम some घातerbooks
 */
#घोषणा MB_POWER_DELAY	200

/*
 * Hold the media-bay reset संकेत true क्रम this many ticks
 * after a device is inserted beक्रमe releasing it.
 */
#घोषणा MB_RESET_DELAY	50

/*
 * Wait this दीर्घ after the reset संकेत is released and beक्रमe करोing
 * further operations. After this delay, the IDE reset संकेत is released
 * too क्रम an IDE device
 */
#घोषणा MB_SETUP_DELAY	100

/*
 * Wait this many ticks after an IDE device (e.g. CD-ROM) is inserted
 * (or until the device is पढ़ोy) beक्रमe calling पूर्णांकo the driver
 */
#घोषणा MB_IDE_WAIT	1000

/*
 * States of a media bay
 */
क्रमागत अणु
	mb_empty = 0,		/* Idle */
	mb_घातering_up,		/* घातer bit set, रुकोing MB_POWER_DELAY */
	mb_enabling_bay,	/* enable bits set, रुकोing MB_RESET_DELAY */
	mb_resetting,		/* reset bit unset, रुकोing MB_SETUP_DELAY */
	mb_ide_resetting,	/* IDE reset bit unser, रुकोing MB_IDE_WAIT */
	mb_up,			/* Media bay full */
	mb_घातering_करोwn	/* Powering करोwn (aव्योम too fast करोwn/up) */
पूर्ण;

#घोषणा MB_POWER_SOUND		0x08
#घोषणा MB_POWER_FLOPPY		0x04
#घोषणा MB_POWER_ATA		0x02
#घोषणा MB_POWER_PCI		0x01
#घोषणा MB_POWER_OFF		0x00

/*
 * Functions क्रम polling content of media bay
 */
 
अटल u8
ohare_mb_content(काष्ठा media_bay_info *bay)
अणु
	वापस (MB_IN32(bay, OHARE_MBCR) >> 12) & 7;
पूर्ण

अटल u8
heathrow_mb_content(काष्ठा media_bay_info *bay)
अणु
	वापस (MB_IN32(bay, HEATHROW_MBCR) >> 12) & 7;
पूर्ण

अटल u8
keylargo_mb_content(काष्ठा media_bay_info *bay)
अणु
	पूर्णांक new_gpio;

	new_gpio = MB_IN8(bay, KL_GPIO_MEDIABAY_IRQ) & KEYLARGO_GPIO_INPUT_DATA;
	अगर (new_gpio) अणु
		bay->cached_gpio = new_gpio;
		वापस MB_NO;
	पूर्ण अन्यथा अगर (bay->cached_gpio != new_gpio) अणु
		MB_BIS(bay, KEYLARGO_MBCR, KL_MBCR_MB0_ENABLE);
		(व्योम)MB_IN32(bay, KEYLARGO_MBCR);
		udelay(5);
		MB_BIC(bay, KEYLARGO_MBCR, 0x0000000F);
		(व्योम)MB_IN32(bay, KEYLARGO_MBCR);
		udelay(5);
		bay->cached_gpio = new_gpio;
	पूर्ण
	वापस (MB_IN32(bay, KEYLARGO_MBCR) >> 4) & 7;
पूर्ण

/*
 * Functions क्रम घातering up/करोwn the bay, माला_दो the bay device
 * पूर्णांकo reset state as well
 */

अटल व्योम
ohare_mb_घातer(काष्ठा media_bay_info* bay, पूर्णांक on_off)
अणु
	अगर (on_off) अणु
		/* Power up device, निश्चित it's reset line */
		MB_BIC(bay, OHARE_FCR, OH_BAY_RESET_N);
		MB_BIC(bay, OHARE_FCR, OH_BAY_POWER_N);
	पूर्ण अन्यथा अणु
		/* Disable all devices */
		MB_BIC(bay, OHARE_FCR, OH_BAY_DEV_MASK);
		MB_BIC(bay, OHARE_FCR, OH_FLOPPY_ENABLE);
		/* Cut घातer from bay, release reset line */
		MB_BIS(bay, OHARE_FCR, OH_BAY_POWER_N);
		MB_BIS(bay, OHARE_FCR, OH_BAY_RESET_N);
		MB_BIS(bay, OHARE_FCR, OH_IDE1_RESET_N);
	पूर्ण
	MB_BIC(bay, OHARE_MBCR, 0x00000F00);
पूर्ण

अटल व्योम
heathrow_mb_घातer(काष्ठा media_bay_info* bay, पूर्णांक on_off)
अणु
	अगर (on_off) अणु
		/* Power up device, निश्चित it's reset line */
		MB_BIC(bay, HEATHROW_FCR, HRW_BAY_RESET_N);
		MB_BIC(bay, HEATHROW_FCR, HRW_BAY_POWER_N);
	पूर्ण अन्यथा अणु
		/* Disable all devices */
		MB_BIC(bay, HEATHROW_FCR, HRW_BAY_DEV_MASK);
		MB_BIC(bay, HEATHROW_FCR, HRW_SWIM_ENABLE);
		/* Cut घातer from bay, release reset line */
		MB_BIS(bay, HEATHROW_FCR, HRW_BAY_POWER_N);
		MB_BIS(bay, HEATHROW_FCR, HRW_BAY_RESET_N);
		MB_BIS(bay, HEATHROW_FCR, HRW_IDE1_RESET_N);
	पूर्ण
	MB_BIC(bay, HEATHROW_MBCR, 0x00000F00);
पूर्ण

अटल व्योम
keylargo_mb_घातer(काष्ठा media_bay_info* bay, पूर्णांक on_off)
अणु
	अगर (on_off) अणु
		/* Power up device, निश्चित it's reset line */
            	MB_BIC(bay, KEYLARGO_MBCR, KL_MBCR_MB0_DEV_RESET);
            	MB_BIC(bay, KEYLARGO_MBCR, KL_MBCR_MB0_DEV_POWER);
	पूर्ण अन्यथा अणु
		/* Disable all devices */
		MB_BIC(bay, KEYLARGO_MBCR, KL_MBCR_MB0_DEV_MASK);
		MB_BIC(bay, KEYLARGO_FCR1, KL1_EIDE0_ENABLE);
		/* Cut घातer from bay, release reset line */
		MB_BIS(bay, KEYLARGO_MBCR, KL_MBCR_MB0_DEV_POWER);
		MB_BIS(bay, KEYLARGO_MBCR, KL_MBCR_MB0_DEV_RESET);
		MB_BIS(bay, KEYLARGO_FCR1, KL1_EIDE0_RESET_N);
	पूर्ण
	MB_BIC(bay, KEYLARGO_MBCR, 0x0000000F);
पूर्ण

/*
 * Functions क्रम configuring the media bay क्रम a given type of device,
 * enable the related busses
 */

अटल पूर्णांक
ohare_mb_setup_bus(काष्ठा media_bay_info* bay, u8 device_id)
अणु
	चयन(device_id) अणु
		हाल MB_FD:
		हाल MB_FD1:
			MB_BIS(bay, OHARE_FCR, OH_BAY_FLOPPY_ENABLE);
			MB_BIS(bay, OHARE_FCR, OH_FLOPPY_ENABLE);
			वापस 0;
		हाल MB_CD:
			MB_BIC(bay, OHARE_FCR, OH_IDE1_RESET_N);
			MB_BIS(bay, OHARE_FCR, OH_BAY_IDE_ENABLE);
			वापस 0;
		हाल MB_PCI:
			MB_BIS(bay, OHARE_FCR, OH_BAY_PCI_ENABLE);
			वापस 0;
	पूर्ण
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक
heathrow_mb_setup_bus(काष्ठा media_bay_info* bay, u8 device_id)
अणु
	चयन(device_id) अणु
		हाल MB_FD:
		हाल MB_FD1:
			MB_BIS(bay, HEATHROW_FCR, HRW_BAY_FLOPPY_ENABLE);
			MB_BIS(bay, HEATHROW_FCR, HRW_SWIM_ENABLE);
			वापस 0;
		हाल MB_CD:
			MB_BIC(bay, HEATHROW_FCR, HRW_IDE1_RESET_N);
			MB_BIS(bay, HEATHROW_FCR, HRW_BAY_IDE_ENABLE);
			वापस 0;
		हाल MB_PCI:
			MB_BIS(bay, HEATHROW_FCR, HRW_BAY_PCI_ENABLE);
			वापस 0;
	पूर्ण
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक
keylargo_mb_setup_bus(काष्ठा media_bay_info* bay, u8 device_id)
अणु
	चयन(device_id) अणु
		हाल MB_CD:
			MB_BIS(bay, KEYLARGO_MBCR, KL_MBCR_MB0_IDE_ENABLE);
			MB_BIC(bay, KEYLARGO_FCR1, KL1_EIDE0_RESET_N);
			MB_BIS(bay, KEYLARGO_FCR1, KL1_EIDE0_ENABLE);
			वापस 0;
		हाल MB_PCI:
			MB_BIS(bay, KEYLARGO_MBCR, KL_MBCR_MB0_PCI_ENABLE);
			वापस 0;
		हाल MB_SOUND:
			MB_BIS(bay, KEYLARGO_MBCR, KL_MBCR_MB0_SOUND_ENABLE);
			वापस 0;
	पूर्ण
	वापस -ENODEV;
पूर्ण

/*
 * Functions क्रम tweaking resets
 */

अटल व्योम
ohare_mb_un_reset(काष्ठा media_bay_info* bay)
अणु
	MB_BIS(bay, OHARE_FCR, OH_BAY_RESET_N);
पूर्ण

अटल व्योम keylargo_mb_init(काष्ठा media_bay_info *bay)
अणु
	MB_BIS(bay, KEYLARGO_MBCR, KL_MBCR_MB0_ENABLE);
पूर्ण

अटल व्योम heathrow_mb_un_reset(काष्ठा media_bay_info* bay)
अणु
	MB_BIS(bay, HEATHROW_FCR, HRW_BAY_RESET_N);
पूर्ण

अटल व्योम keylargo_mb_un_reset(काष्ठा media_bay_info* bay)
अणु
	MB_BIS(bay, KEYLARGO_MBCR, KL_MBCR_MB0_DEV_RESET);
पूर्ण

अटल व्योम ohare_mb_un_reset_ide(काष्ठा media_bay_info* bay)
अणु
	MB_BIS(bay, OHARE_FCR, OH_IDE1_RESET_N);
पूर्ण

अटल व्योम heathrow_mb_un_reset_ide(काष्ठा media_bay_info* bay)
अणु
	MB_BIS(bay, HEATHROW_FCR, HRW_IDE1_RESET_N);
पूर्ण

अटल व्योम keylargo_mb_un_reset_ide(काष्ठा media_bay_info* bay)
अणु
	MB_BIS(bay, KEYLARGO_FCR1, KL1_EIDE0_RESET_N);
पूर्ण

अटल अंतरभूत व्योम set_mb_घातer(काष्ठा media_bay_info* bay, पूर्णांक onoff)
अणु
	/* Power up up and निश्चित the bay reset line */
	अगर (onoff) अणु
		bay->ops->घातer(bay, 1);
		bay->state = mb_घातering_up;
		pr_debug("mediabay%d: powering up\n", bay->index);
	पूर्ण अन्यथा अणु 
		/* Make sure everything is घातered करोwn & disabled */
		bay->ops->घातer(bay, 0);
		bay->state = mb_घातering_करोwn;
		pr_debug("mediabay%d: powering down\n", bay->index);
	पूर्ण
	bay->समयr = msecs_to_jअगरfies(MB_POWER_DELAY);
पूर्ण

अटल व्योम poll_media_bay(काष्ठा media_bay_info* bay)
अणु
	पूर्णांक id = bay->ops->content(bay);

	अटल अक्षर *mb_content_types[] = अणु
		"a floppy drive",
		"a floppy drive",
		"an unsupported audio device",
		"an ATA device",
		"an unsupported PCI device",
		"an unknown device",
	पूर्ण;

	अगर (id != bay->last_value) अणु
		bay->last_value = id;
		bay->value_count = 0;
		वापस;
	पूर्ण
	अगर (id == bay->content_id)
		वापस;

	bay->value_count += msecs_to_jअगरfies(MB_POLL_DELAY);
	अगर (bay->value_count >= msecs_to_jअगरfies(MB_STABLE_DELAY)) अणु
		/* If the device type changes without going thru
		 * "MB_NO", we क्रमce a pass by "MB_NO" to make sure
		 * things are properly reset
		 */
		अगर ((id != MB_NO) && (bay->content_id != MB_NO)) अणु
			id = MB_NO;
			pr_debug("mediabay%d: forcing MB_NO\n", bay->index);
		पूर्ण
		pr_debug("mediabay%d: switching to %d\n", bay->index, id);
		set_mb_घातer(bay, id != MB_NO);
		bay->content_id = id;
		अगर (id >= MB_NO || id < 0)
			prपूर्णांकk(KERN_INFO "mediabay%d: Bay is now empty\n", bay->index);
		अन्यथा
			prपूर्णांकk(KERN_INFO "mediabay%d: Bay contains %s\n",
			       bay->index, mb_content_types[id]);
	पूर्ण
पूर्ण

पूर्णांक check_media_bay(काष्ठा macio_dev *baydev)
अणु
	काष्ठा media_bay_info* bay;
	पूर्णांक id;

	अगर (baydev == शून्य)
		वापस MB_NO;

	/* This वापसs an instant snapshot, not locking, sine
	 * we may be called with the bay lock held. The resulting
	 * fuzzyness of the result अगर called at the wrong समय is
	 * not actually a huge deal
	 */
	bay = macio_get_drvdata(baydev);
	अगर (bay == शून्य)
		वापस MB_NO;
	id = bay->content_id;
	अगर (bay->state != mb_up)
		वापस MB_NO;
	अगर (id == MB_FD1)
		वापस MB_FD;
	वापस id;
पूर्ण
EXPORT_SYMBOL_GPL(check_media_bay);

व्योम lock_media_bay(काष्ठा macio_dev *baydev)
अणु
	काष्ठा media_bay_info* bay;

	अगर (baydev == शून्य)
		वापस;
	bay = macio_get_drvdata(baydev);
	अगर (bay == शून्य)
		वापस;
	mutex_lock(&bay->lock);
	bay->user_lock = 1;
पूर्ण
EXPORT_SYMBOL_GPL(lock_media_bay);

व्योम unlock_media_bay(काष्ठा macio_dev *baydev)
अणु
	काष्ठा media_bay_info* bay;

	अगर (baydev == शून्य)
		वापस;
	bay = macio_get_drvdata(baydev);
	अगर (bay == शून्य)
		वापस;
	अगर (bay->user_lock) अणु
		bay->user_lock = 0;
		mutex_unlock(&bay->lock);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(unlock_media_bay);

अटल पूर्णांक mb_broadcast_hotplug(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा media_bay_info* bay = data;
	काष्ठा macio_dev *mdev;
	काष्ठा macio_driver *drv;
	पूर्णांक state;

	अगर (dev->bus != &macio_bus_type)
		वापस 0;

	state = bay->state == mb_up ? bay->content_id : MB_NO;
	अगर (state == MB_FD1)
		state = MB_FD;
	mdev = to_macio_device(dev);
	drv = to_macio_driver(dev->driver);
	अगर (dev->driver && drv->mediabay_event)
		drv->mediabay_event(mdev, state);
	वापस 0;
पूर्ण

अटल व्योम media_bay_step(पूर्णांक i)
अणु
	काष्ठा media_bay_info* bay = &media_bays[i];

	/* We करोn't poll when घातering करोwn */
	अगर (bay->state != mb_घातering_करोwn)
	    poll_media_bay(bay);

	/* If समयr expired run state machine */
	अगर (bay->समयr != 0) अणु
		bay->समयr -= msecs_to_jअगरfies(MB_POLL_DELAY);
		अगर (bay->समयr > 0)
			वापस;
		bay->समयr = 0;
	पूर्ण

	चयन(bay->state) अणु
	हाल mb_घातering_up:
	    	अगर (bay->ops->setup_bus(bay, bay->last_value) < 0) अणु
			pr_debug("mediabay%d: device not supported (kind:%d)\n",
				 i, bay->content_id);
	    		set_mb_घातer(bay, 0);
	    		अवरोध;
	    	पूर्ण
	    	bay->समयr = msecs_to_jअगरfies(MB_RESET_DELAY);
	    	bay->state = mb_enabling_bay;
		pr_debug("mediabay%d: enabling (kind:%d)\n", i, bay->content_id);
		अवरोध;
	हाल mb_enabling_bay:
		bay->ops->un_reset(bay);
	    	bay->समयr = msecs_to_jअगरfies(MB_SETUP_DELAY);
	    	bay->state = mb_resetting;
		pr_debug("mediabay%d: releasing bay reset (kind:%d)\n",
			 i, bay->content_id);
	    	अवरोध;
	हाल mb_resetting:
		अगर (bay->content_id != MB_CD) अणु
			pr_debug("mediabay%d: bay is up (kind:%d)\n", i,
				 bay->content_id);
			bay->state = mb_up;
			device_क्रम_each_child(&bay->mdev->ofdev.dev,
					      bay, mb_broadcast_hotplug);
			अवरोध;
	    	पूर्ण
		pr_debug("mediabay%d: releasing ATA reset (kind:%d)\n",
			 i, bay->content_id);
		bay->ops->un_reset_ide(bay);
	    	bay->समयr = msecs_to_jअगरfies(MB_IDE_WAIT);
	    	bay->state = mb_ide_resetting;
	    	अवरोध;

	हाल mb_ide_resetting:
		pr_debug("mediabay%d: bay is up (kind:%d)\n", i, bay->content_id);
		bay->state = mb_up;
		device_क्रम_each_child(&bay->mdev->ofdev.dev,
				      bay, mb_broadcast_hotplug);
	    	अवरोध;

	हाल mb_घातering_करोwn:
	    	bay->state = mb_empty;
		device_क्रम_each_child(&bay->mdev->ofdev.dev,
				      bay, mb_broadcast_hotplug);
		pr_debug("mediabay%d: end of power down\n", i);
	    	अवरोध;
	पूर्ण
पूर्ण

/*
 * This procedure runs as a kernel thपढ़ो to poll the media bay
 * once each tick and रेजिस्टर and unरेजिस्टर the IDE पूर्णांकerface
 * with the IDE driver.  It needs to be a thपढ़ो because
 * ide_रेजिस्टर can't be called from पूर्णांकerrupt context.
 */
अटल पूर्णांक media_bay_task(व्योम *x)
अणु
	पूर्णांक	i;

	जबतक (!kthपढ़ो_should_stop()) अणु
		क्रम (i = 0; i < media_bay_count; ++i) अणु
			mutex_lock(&media_bays[i].lock);
			अगर (!media_bays[i].sleeping)
				media_bay_step(i);
			mutex_unlock(&media_bays[i].lock);
		पूर्ण

		msleep_पूर्णांकerruptible(MB_POLL_DELAY);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक media_bay_attach(काष्ठा macio_dev *mdev,
			    स्थिर काष्ठा of_device_id *match)
अणु
	काष्ठा media_bay_info* bay;
	u32 __iomem *regbase;
	काष्ठा device_node *ofnode;
	अचिन्हित दीर्घ base;
	पूर्णांक i;

	ofnode = mdev->ofdev.dev.of_node;

	अगर (macio_resource_count(mdev) < 1)
		वापस -ENODEV;
	अगर (macio_request_resources(mdev, "media-bay"))
		वापस -EBUSY;
	/* Media bay रेजिस्टरs are located at the beginning of the
         * mac-io chip, क्रम now, we trick and align करोwn the first
	 * resource passed in
         */
	base = macio_resource_start(mdev, 0) & 0xffff0000u;
	regbase = (u32 __iomem *)ioremap(base, 0x100);
	अगर (regbase == शून्य) अणु
		macio_release_resources(mdev);
		वापस -ENOMEM;
	पूर्ण
	
	i = media_bay_count++;
	bay = &media_bays[i];
	bay->mdev = mdev;
	bay->base = regbase;
	bay->index = i;
	bay->ops = match->data;
	bay->sleeping = 0;
	mutex_init(&bay->lock);

	/* Init HW probing */
	अगर (bay->ops->init)
		bay->ops->init(bay);

	prपूर्णांकk(KERN_INFO "mediabay%d: Registered %s media-bay\n", i, bay->ops->name);

	/* Force an immediate detect */
	set_mb_घातer(bay, 0);
	msleep(MB_POWER_DELAY);
	bay->content_id = MB_NO;
	bay->last_value = bay->ops->content(bay);
	bay->value_count = msecs_to_jअगरfies(MB_STABLE_DELAY);
	bay->state = mb_empty;

	/* Mark us पढ़ोy by filling our mdev data */
	macio_set_drvdata(mdev, bay);

	/* Startup kernel thपढ़ो */
	अगर (i == 0)
		kthपढ़ो_run(media_bay_task, शून्य, "media-bay");

	वापस 0;

पूर्ण

अटल पूर्णांक media_bay_suspend(काष्ठा macio_dev *mdev, pm_message_t state)
अणु
	काष्ठा media_bay_info	*bay = macio_get_drvdata(mdev);

	अगर (state.event != mdev->ofdev.dev.घातer.घातer_state.event
	    && (state.event & PM_EVENT_SLEEP)) अणु
		mutex_lock(&bay->lock);
		bay->sleeping = 1;
		set_mb_घातer(bay, 0);
		mutex_unlock(&bay->lock);
		msleep(MB_POLL_DELAY);
		mdev->ofdev.dev.घातer.घातer_state = state;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक media_bay_resume(काष्ठा macio_dev *mdev)
अणु
	काष्ठा media_bay_info	*bay = macio_get_drvdata(mdev);

	अगर (mdev->ofdev.dev.घातer.घातer_state.event != PM_EVENT_ON) अणु
		mdev->ofdev.dev.घातer.घातer_state = PMSG_ON;

	       	/* We re-enable the bay using it's previous content
	       	   only अगर it did not change. Note those bozo timings,
	       	   they seem to help the 3400 get it right.
	       	 */
	       	/* Force MB घातer to 0 */
		mutex_lock(&bay->lock);
	       	set_mb_घातer(bay, 0);
		msleep(MB_POWER_DELAY);
	       	अगर (bay->ops->content(bay) != bay->content_id) अणु
			prपूर्णांकk("mediabay%d: Content changed during sleep...\n", bay->index);
			mutex_unlock(&bay->lock);
	       		वापस 0;
		पूर्ण
	       	set_mb_घातer(bay, 1);
	       	bay->last_value = bay->content_id;
	       	bay->value_count = msecs_to_jअगरfies(MB_STABLE_DELAY);
	       	bay->समयr = msecs_to_jअगरfies(MB_POWER_DELAY);
	       	करो अणु
			msleep(MB_POLL_DELAY);
	       		media_bay_step(bay->index);
	       	पूर्ण जबतक((bay->state != mb_empty) &&
	       		(bay->state != mb_up));
		bay->sleeping = 0;
		mutex_unlock(&bay->lock);
	पूर्ण
	वापस 0;
पूर्ण


/* Definitions of "ops" काष्ठाures.
 */
अटल स्थिर काष्ठा mb_ops ohare_mb_ops = अणु
	.name		= "Ohare",
	.content	= ohare_mb_content,
	.घातer		= ohare_mb_घातer,
	.setup_bus	= ohare_mb_setup_bus,
	.un_reset	= ohare_mb_un_reset,
	.un_reset_ide	= ohare_mb_un_reset_ide,
पूर्ण;

अटल स्थिर काष्ठा mb_ops heathrow_mb_ops = अणु
	.name		= "Heathrow",
	.content	= heathrow_mb_content,
	.घातer		= heathrow_mb_घातer,
	.setup_bus	= heathrow_mb_setup_bus,
	.un_reset	= heathrow_mb_un_reset,
	.un_reset_ide	= heathrow_mb_un_reset_ide,
पूर्ण;

अटल स्थिर काष्ठा mb_ops keylargo_mb_ops = अणु
	.name		= "KeyLargo",
	.init		= keylargo_mb_init,
	.content	= keylargo_mb_content,
	.घातer		= keylargo_mb_घातer,
	.setup_bus	= keylargo_mb_setup_bus,
	.un_reset	= keylargo_mb_un_reset,
	.un_reset_ide	= keylargo_mb_un_reset_ide,
पूर्ण;

/*
 * It seems that the bit क्रम the media-bay पूर्णांकerrupt in the IRQ_LEVEL
 * रेजिस्टर is always set when there is something in the media bay.
 * This causes problems क्रम the पूर्णांकerrupt code अगर we attach an पूर्णांकerrupt
 * handler to the media-bay पूर्णांकerrupt, because it tends to go पूर्णांकo
 * an infinite loop calling the media bay पूर्णांकerrupt handler.
 * Thereक्रमe we करो it all by polling the media bay once each tick.
 */

अटल काष्ठा of_device_id media_bay_match[] =
अणु
	अणु
	.name		= "media-bay",
	.compatible	= "keylargo-media-bay",
	.data		= &keylargo_mb_ops,
	पूर्ण,
	अणु
	.name		= "media-bay",
	.compatible	= "heathrow-media-bay",
	.data		= &heathrow_mb_ops,
	पूर्ण,
	अणु
	.name		= "media-bay",
	.compatible	= "ohare-media-bay",
	.data		= &ohare_mb_ops,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा macio_driver media_bay_driver =
अणु
	.driver = अणु
		.name		= "media-bay",
		.of_match_table	= media_bay_match,
	पूर्ण,
	.probe		= media_bay_attach,
	.suspend	= media_bay_suspend,
	.resume		= media_bay_resume
पूर्ण;

अटल पूर्णांक __init media_bay_init(व्योम)
अणु
	पूर्णांक i;

	क्रम (i=0; i<MAX_BAYS; i++) अणु
		स_रखो((अक्षर *)&media_bays[i], 0, माप(काष्ठा media_bay_info));
		media_bays[i].content_id	= -1;
	पूर्ण
	अगर (!machine_is(घातermac))
		वापस 0;

	macio_रेजिस्टर_driver(&media_bay_driver);	

	वापस 0;
पूर्ण

device_initcall(media_bay_init);
