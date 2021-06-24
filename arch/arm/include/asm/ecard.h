<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * arch/arm/include/यंत्र/ecard.h
 *
 * definitions क्रम expansion cards
 *
 * This is a new प्रणाली as from Linux 1.2.3
 *
 * Changelog:
 *  11-12-1996	RMK	Further minor improvements
 *  12-09-1997	RMK	Added पूर्णांकerrupt enable/disable क्रम card level
 *
 * Reference: Acorns Risc OS 3 Programmers Reference Manuals.
 */

#अगर_अघोषित __ASM_ECARD_H
#घोषणा __ASM_ECARD_H

/*
 * Currently understood cards (but not necessarily
 * supported):
 *                        Manufacturer  Product ID
 */
#घोषणा MANU_ACORN		0x0000
#घोषणा PROD_ACORN_SCSI			0x0002
#घोषणा PROD_ACORN_ETHER1		0x0003
#घोषणा PROD_ACORN_MFM			0x000b

#घोषणा MANU_ANT2		0x0011
#घोषणा PROD_ANT_ETHER3			0x00a4

#घोषणा MANU_ATOMWIDE		0x0017
#घोषणा PROD_ATOMWIDE_3PSERIAL		0x0090

#घोषणा MANU_IRLAM_INSTRUMENTS	0x001f
#घोषणा MANU_IRLAM_INSTRUMENTS_ETHERN	0x5678

#घोषणा MANU_OAK		0x0021
#घोषणा PROD_OAK_SCSI			0x0058

#घोषणा MANU_MORLEY		0x002b
#घोषणा PROD_MORLEY_SCSI_UNCACHED	0x0067

#घोषणा MANU_CUMANA		0x003a
#घोषणा PROD_CUMANA_SCSI_2		0x003a
#घोषणा PROD_CUMANA_SCSI_1		0x00a0

#घोषणा MANU_ICS		0x003c
#घोषणा PROD_ICS_IDE			0x00ae

#घोषणा MANU_ICS2		0x003d
#घोषणा PROD_ICS2_IDE			0x00ae

#घोषणा MANU_SERPORT		0x003f
#घोषणा PROD_SERPORT_DSPORT		0x00b9

#घोषणा MANU_ARXE		0x0041
#घोषणा PROD_ARXE_SCSI			0x00be

#घोषणा MANU_I3			0x0046
#घोषणा PROD_I3_ETHERLAN500		0x00d4
#घोषणा PROD_I3_ETHERLAN600		0x00ec
#घोषणा PROD_I3_ETHERLAN600A		0x011e

#घोषणा MANU_ANT		0x0053
#घोषणा PROD_ANT_ETHERM			0x00d8
#घोषणा PROD_ANT_ETHERB			0x00e4

#घोषणा MANU_ALSYSTEMS		0x005b
#घोषणा PROD_ALSYS_SCSIATAPI		0x0107

#घोषणा MANU_MCS		0x0063
#घोषणा PROD_MCS_CONNECT32		0x0125

#घोषणा MANU_EESOX		0x0064
#घोषणा PROD_EESOX_SCSI2		0x008c

#घोषणा MANU_YELLOWSTONE	0x0096
#घोषणा PROD_YELLOWSTONE_RAPIDE32	0x0120

#अगर_घोषित ECARD_C
#घोषणा CONST
#अन्यथा
#घोषणा CONST स्थिर
#पूर्ण_अगर

#घोषणा MAX_ECARDS	9

काष्ठा ecard_id अणु			/* Card ID काष्ठाure		*/
	अचिन्हित लघु	manufacturer;
	अचिन्हित लघु	product;
	व्योम		*data;
पूर्ण;

काष्ठा in_ecid अणु			/* Packed card ID inक्रमmation	*/
	अचिन्हित लघु	product;	/* Product code			*/
	अचिन्हित लघु	manufacturer;	/* Manufacturer code		*/
	अचिन्हित अक्षर	id:4;		/* Simple ID			*/
	अचिन्हित अक्षर	cd:1;		/* Chunk dir present		*/
	अचिन्हित अक्षर	is:1;		/* Interrupt status poपूर्णांकers	*/
	अचिन्हित अक्षर	w:2;		/* Width			*/
	अचिन्हित अक्षर	country;	/* Country			*/
	अचिन्हित अक्षर	irqmask;	/* IRQ mask			*/
	अचिन्हित अक्षर	fiqmask;	/* FIQ mask			*/
	अचिन्हित दीर्घ	irqoff;		/* IRQ offset			*/
	अचिन्हित दीर्घ	fiqoff;		/* FIQ offset			*/
पूर्ण;

प्रकार काष्ठा expansion_card ecard_t;
प्रकार अचिन्हित दीर्घ *loader_t;

प्रकार काष्ठा expansion_card_ops अणु	/* Card handler routines	*/
	व्योम (*irqenable)(ecard_t *ec, पूर्णांक irqnr);
	व्योम (*irqdisable)(ecard_t *ec, पूर्णांक irqnr);
	पूर्णांक  (*irqpending)(ecard_t *ec);
	व्योम (*fiqenable)(ecard_t *ec, पूर्णांक fiqnr);
	व्योम (*fiqdisable)(ecard_t *ec, पूर्णांक fiqnr);
	पूर्णांक  (*fiqpending)(ecard_t *ec);
पूर्ण expansioncard_ops_t;

#घोषणा ECARD_NUM_RESOURCES	(6)

#घोषणा ECARD_RES_IOCSLOW	(0)
#घोषणा ECARD_RES_IOCMEDIUM	(1)
#घोषणा ECARD_RES_IOCFAST	(2)
#घोषणा ECARD_RES_IOCSYNC	(3)
#घोषणा ECARD_RES_MEMC		(4)
#घोषणा ECARD_RES_EASI		(5)

#घोषणा ecard_resource_start(ec,nr)	((ec)->resource[nr].start)
#घोषणा ecard_resource_end(ec,nr)	((ec)->resource[nr].end)
#घोषणा ecard_resource_len(ec,nr)	((ec)->resource[nr].end - \
					 (ec)->resource[nr].start + 1)
#घोषणा ecard_resource_flags(ec,nr)	((ec)->resource[nr].flags)

/*
 * This contains all the info needed on an expansion card
 */
काष्ठा expansion_card अणु
	काष्ठा expansion_card  *next;

	काष्ठा device		dev;
	काष्ठा resource		resource[ECARD_NUM_RESOURCES];

	/* Public data */
	व्योम __iomem		*irqaddr;	/* address of IRQ रेजिस्टर	*/
	व्योम __iomem		*fiqaddr;	/* address of FIQ रेजिस्टर	*/
	अचिन्हित अक्षर		irqmask;	/* IRQ mask			*/
	अचिन्हित अक्षर		fiqmask;	/* FIQ mask			*/
	अचिन्हित अक्षर  		claimed;	/* Card claimed?		*/
	अचिन्हित अक्षर		easi;		/* EASI card			*/

	व्योम			*irq_data;	/* Data क्रम use क्रम IRQ by card	*/
	व्योम			*fiq_data;	/* Data क्रम use क्रम FIQ by card	*/
	स्थिर expansioncard_ops_t *ops;		/* Enable/Disable Ops क्रम card	*/

	CONST अचिन्हित पूर्णांक	slot_no;	/* Slot number			*/
	CONST अचिन्हित पूर्णांक	dma;		/* DMA number (क्रम request_dma)	*/
	CONST अचिन्हित पूर्णांक	irq;		/* IRQ number (क्रम request_irq)	*/
	CONST अचिन्हित पूर्णांक	fiq;		/* FIQ number (क्रम request_irq)	*/
	CONST काष्ठा in_ecid	cid;		/* Card Identअगरication		*/

	/* Private पूर्णांकernal data */
	स्थिर अक्षर		*card_desc;	/* Card description		*/
	CONST loader_t		loader;		/* loader program */
	u64			dma_mask;
पूर्ण;

व्योम ecard_setirq(काष्ठा expansion_card *ec, स्थिर काष्ठा expansion_card_ops *ops, व्योम *irq_data);

काष्ठा in_chunk_dir अणु
	अचिन्हित पूर्णांक start_offset;
	जोड़ अणु
		अचिन्हित अक्षर string[256];
		अचिन्हित अक्षर data[1];
	पूर्ण d;
पूर्ण;

/*
 * Read a chunk from an expansion card
 * cd : where to put पढ़ो data
 * ec : expansion card info काष्ठा
 * id : id number to find
 * num: (n+1)'th id to find.
 */
बाह्य पूर्णांक ecard_पढ़ोchunk (काष्ठा in_chunk_dir *cd, काष्ठा expansion_card *ec, पूर्णांक id, पूर्णांक num);

/*
 * Request and release ecard resources
 */
बाह्य पूर्णांक ecard_request_resources(काष्ठा expansion_card *ec);
बाह्य व्योम ecard_release_resources(काष्ठा expansion_card *ec);

व्योम __iomem *ecardm_iomap(काष्ठा expansion_card *ec, अचिन्हित पूर्णांक res,
			   अचिन्हित दीर्घ offset, अचिन्हित दीर्घ maxsize);
#घोषणा ecardm_iounmap(__ec, __addr)	devm_iounmap(&(__ec)->dev, __addr)

बाह्य काष्ठा bus_type ecard_bus_type;

#घोषणा ECARD_DEV(_d)	container_of((_d), काष्ठा expansion_card, dev)

काष्ठा ecard_driver अणु
	पूर्णांक			(*probe)(काष्ठा expansion_card *, स्थिर काष्ठा ecard_id *id);
	व्योम			(*हटाओ)(काष्ठा expansion_card *);
	व्योम			(*shutकरोwn)(काष्ठा expansion_card *);
	स्थिर काष्ठा ecard_id	*id_table;
	अचिन्हित पूर्णांक		id;
	काष्ठा device_driver	drv;
पूर्ण;

#घोषणा ECARD_DRV(_d)	container_of((_d), काष्ठा ecard_driver, drv)

#घोषणा ecard_set_drvdata(ec,data)	dev_set_drvdata(&(ec)->dev, (data))
#घोषणा ecard_get_drvdata(ec)		dev_get_drvdata(&(ec)->dev)

पूर्णांक ecard_रेजिस्टर_driver(काष्ठा ecard_driver *);
व्योम ecard_हटाओ_driver(काष्ठा ecard_driver *);

#पूर्ण_अगर
