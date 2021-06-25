<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __MCB_INTERNAL
#घोषणा __MCB_INTERNAL

#समावेश <linux/types.h>

#घोषणा PCI_VENDOR_ID_MEN		0x1a88
#घोषणा PCI_DEVICE_ID_MEN_CHAMELEON	0x4d45
#घोषणा CHAMELEONV2_MAGIC		0xabce
#घोषणा CHAM_HEADER_SIZE		0x200

क्रमागत chameleon_descriptor_type अणु
	CHAMELEON_DTYPE_GENERAL = 0x0,
	CHAMELEON_DTYPE_BRIDGE = 0x1,
	CHAMELEON_DTYPE_CPU = 0x2,
	CHAMELEON_DTYPE_BAR = 0x3,
	CHAMELEON_DTYPE_END = 0xf,
पूर्ण;

क्रमागत chameleon_bus_type अणु
	CHAMELEON_BUS_WISHBONE,
	CHAMELEON_BUS_AVALON,
	CHAMELEON_BUS_LPC,
	CHAMELEON_BUS_ISA,
पूर्ण;

/**
 * काष्ठा chameleon_fpga_header
 *
 * @revision:	Revison of Chameleon table in FPGA
 * @model:	Chameleon table model ASCII अक्षर
 * @minor:	Revision minor
 * @bus_type:	Bus type (usually %CHAMELEON_BUS_WISHBONE)
 * @magic:	Chameleon header magic number (0xabce क्रम version 2)
 * @reserved:	Reserved
 * @filename:	Filename of FPGA bitstream
 */
काष्ठा chameleon_fpga_header अणु
	u8 revision;
	अक्षर model;
	u8 minor;
	u8 bus_type;
	u16 magic;
	u16 reserved;
	/* This one has no '\0' at the end!!! */
	अक्षर filename[CHAMELEON_खाताNAME_LEN];
पूर्ण __packed;
#घोषणा HEADER_MAGIC_OFFSET 0x4

/**
 * काष्ठा chameleon_gdd - Chameleon General Device Descriptor
 *
 * @irq:	the position in the FPGA's IRQ controller vector
 * @rev:	the revision of the variant's implementation
 * @var:	the variant of the IP core
 * @dev:	the device  the IP core is
 * @dtype:	device descriptor type
 * @bar:	BAR offset that must be added to module offset
 * @inst:	the instance number of the device, 0 is first instance
 * @group:	the group the device beदीर्घs to (0 = no group)
 * @reserved:	reserved
 * @offset:	beginning of the address winकरोw of desired module
 * @size:	size of the module's address winकरोw
 */
काष्ठा chameleon_gdd अणु
	__le32 reg1;
	__le32 reg2;
	__le32 offset;
	__le32 size;

पूर्ण __packed;

/* GDD Register 1 fields */
#घोषणा GDD_IRQ(x) ((x) & 0x1f)
#घोषणा GDD_REV(x) (((x) >> 5) & 0x3f)
#घोषणा GDD_VAR(x) (((x) >> 11) & 0x3f)
#घोषणा GDD_DEV(x) (((x) >> 18) & 0x3ff)
#घोषणा GDD_DTY(x) (((x) >> 28) & 0xf)

/* GDD Register 2 fields */
#घोषणा GDD_BAR(x) ((x) & 0x7)
#घोषणा GDD_INS(x) (((x) >> 3) & 0x3f)
#घोषणा GDD_GRP(x) (((x) >> 9) & 0x3f)

/**
 * काष्ठा chameleon_bdd - Chameleon Bridge Device Descriptor
 *
 * @irq:	the position in the FPGA's IRQ controller vector
 * @rev:	the revision of the variant's implementation
 * @var:	the variant of the IP core
 * @dev:	the device  the IP core is
 * @dtype:	device descriptor type
 * @bar:	BAR offset that must be added to module offset
 * @inst:	the instance number of the device, 0 is first instance
 * @dbar:	destination bar from the bus _behind_ the bridge
 * @chamoff:	offset within the BAR of the source bus
 * @offset:
 * @size:
 */
काष्ठा chameleon_bdd अणु
	अचिन्हित पूर्णांक irq:6;
	अचिन्हित पूर्णांक rev:6;
	अचिन्हित पूर्णांक var:6;
	अचिन्हित पूर्णांक dev:10;
	अचिन्हित पूर्णांक dtype:4;
	अचिन्हित पूर्णांक bar:3;
	अचिन्हित पूर्णांक inst:6;
	अचिन्हित पूर्णांक dbar:3;
	अचिन्हित पूर्णांक group:6;
	अचिन्हित पूर्णांक reserved:14;
	u32 chamoff;
	u32 offset;
	u32 size;
पूर्ण __packed;

काष्ठा chameleon_bar अणु
	u32 addr;
	u32 size;
पूर्ण;

#घोषणा BAR_CNT(x) ((x) & 0x07)
#घोषणा CHAMELEON_BAR_MAX	6
#घोषणा BAR_DESC_SIZE(x)	((x) * माप(काष्ठा chameleon_bar) + माप(__le32))

पूर्णांक chameleon_parse_cells(काष्ठा mcb_bus *bus, phys_addr_t mapbase,
			  व्योम __iomem *base);

#पूर्ण_अगर
