<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_PARISC_PARISC_DEVICE_H_
#घोषणा _ASM_PARISC_PARISC_DEVICE_H_

#समावेश <linux/device.h>

काष्ठा parisc_device अणु
	काष्ठा resource hpa;		/* Hard Physical Address */
	काष्ठा parisc_device_id id;
	काष्ठा parisc_driver *driver;	/* Driver क्रम this device */
	अक्षर		name[80];	/* The hardware description */
	पूर्णांक		irq;
	पूर्णांक		aux_irq;	/* Some devices have a second IRQ */

	अक्षर		hw_path;        /* The module number on this bus */
	अचिन्हित पूर्णांक	num_addrs;	/* some devices have additional address ranges. */
	अचिन्हित दीर्घ	*addr;          /* which will be stored here */
 
#अगर_घोषित CONFIG_64BIT
	/* parms क्रम pdc_pat_cell_module() call */
	अचिन्हित दीर्घ	pcell_loc;	/* Physical Cell location */
	अचिन्हित दीर्घ	mod_index;	/* PAT specअगरic - Misc Module info */

	/* generic info वापसed from pdc_pat_cell_module() */
	अचिन्हित दीर्घ	mod_info;	/* PAT specअगरic - Misc Module info */
	अचिन्हित दीर्घ	pmod_loc;	/* physical Module location */
	अचिन्हित दीर्घ	mod0;
#पूर्ण_अगर
	u64		dma_mask;	/* DMA mask क्रम I/O */
	काष्ठा device 	dev;
पूर्ण;

काष्ठा parisc_driver अणु
	काष्ठा parisc_driver *next;
	अक्षर *name; 
	स्थिर काष्ठा parisc_device_id *id_table;
	पूर्णांक (*probe) (काष्ठा parisc_device *dev); /* New device discovered */
	पूर्णांक (*हटाओ) (काष्ठा parisc_device *dev);
	काष्ठा device_driver drv;
पूर्ण;


#घोषणा to_parisc_device(d)	container_of(d, काष्ठा parisc_device, dev)
#घोषणा to_parisc_driver(d)	container_of(d, काष्ठा parisc_driver, drv)
#घोषणा parisc_parent(d)	to_parisc_device(d->dev.parent)

अटल अंतरभूत स्थिर अक्षर *parisc_pathname(काष्ठा parisc_device *d)
अणु
	वापस dev_name(&d->dev);
पूर्ण

अटल अंतरभूत व्योम
parisc_set_drvdata(काष्ठा parisc_device *d, व्योम *p)
अणु
	dev_set_drvdata(&d->dev, p);
पूर्ण

अटल अंतरभूत व्योम *
parisc_get_drvdata(काष्ठा parisc_device *d)
अणु
	वापस dev_get_drvdata(&d->dev);
पूर्ण

बाह्य काष्ठा bus_type parisc_bus_type;

पूर्णांक iosapic_serial_irq(काष्ठा parisc_device *dev);

#पूर्ण_अगर /*_ASM_PARISC_PARISC_DEVICE_H_*/
