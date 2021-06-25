<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause */
#अगर_अघोषित _LINUX_FW_CFG_H
#घोषणा _LINUX_FW_CFG_H

#समावेश <linux/types.h>

#घोषणा FW_CFG_ACPI_DEVICE_ID	"QEMU0002"

/* selector key values क्रम "well-known" fw_cfg entries */
#घोषणा FW_CFG_SIGNATURE	0x00
#घोषणा FW_CFG_ID		0x01
#घोषणा FW_CFG_UUID		0x02
#घोषणा FW_CFG_RAM_SIZE		0x03
#घोषणा FW_CFG_NOGRAPHIC	0x04
#घोषणा FW_CFG_NB_CPUS		0x05
#घोषणा FW_CFG_MACHINE_ID	0x06
#घोषणा FW_CFG_KERNEL_ADDR	0x07
#घोषणा FW_CFG_KERNEL_SIZE	0x08
#घोषणा FW_CFG_KERNEL_CMDLINE	0x09
#घोषणा FW_CFG_INITRD_ADDR	0x0a
#घोषणा FW_CFG_INITRD_SIZE	0x0b
#घोषणा FW_CFG_BOOT_DEVICE	0x0c
#घोषणा FW_CFG_NUMA		0x0d
#घोषणा FW_CFG_BOOT_MENU	0x0e
#घोषणा FW_CFG_MAX_CPUS		0x0f
#घोषणा FW_CFG_KERNEL_ENTRY	0x10
#घोषणा FW_CFG_KERNEL_DATA	0x11
#घोषणा FW_CFG_INITRD_DATA	0x12
#घोषणा FW_CFG_CMDLINE_ADDR	0x13
#घोषणा FW_CFG_CMDLINE_SIZE	0x14
#घोषणा FW_CFG_CMDLINE_DATA	0x15
#घोषणा FW_CFG_SETUP_ADDR	0x16
#घोषणा FW_CFG_SETUP_SIZE	0x17
#घोषणा FW_CFG_SETUP_DATA	0x18
#घोषणा FW_CFG_खाता_सूची		0x19

#घोषणा FW_CFG_खाता_FIRST	0x20
#घोषणा FW_CFG_खाता_SLOTS_MIN	0x10

#घोषणा FW_CFG_WRITE_CHANNEL	0x4000
#घोषणा FW_CFG_ARCH_LOCAL	0x8000
#घोषणा FW_CFG_ENTRY_MASK	(~(FW_CFG_WRITE_CHANNEL | FW_CFG_ARCH_LOCAL))

#घोषणा FW_CFG_INVALID		0xffff

/* width in bytes of fw_cfg control रेजिस्टर */
#घोषणा FW_CFG_CTL_SIZE		0x02

/* fw_cfg "file name" is up to 56 अक्षरacters (including terminating nul) */
#घोषणा FW_CFG_MAX_खाता_PATH	56

/* size in bytes of fw_cfg signature */
#घोषणा FW_CFG_SIG_SIZE 4

/* FW_CFG_ID bits */
#घोषणा FW_CFG_VERSION		0x01
#घोषणा FW_CFG_VERSION_DMA	0x02

/* fw_cfg file directory entry type */
काष्ठा fw_cfg_file अणु
	__be32 size;
	__be16 select;
	__u16 reserved;
	अक्षर name[FW_CFG_MAX_खाता_PATH];
पूर्ण;

/* FW_CFG_DMA_CONTROL bits */
#घोषणा FW_CFG_DMA_CTL_ERROR	0x01
#घोषणा FW_CFG_DMA_CTL_READ	0x02
#घोषणा FW_CFG_DMA_CTL_SKIP	0x04
#घोषणा FW_CFG_DMA_CTL_SELECT	0x08
#घोषणा FW_CFG_DMA_CTL_WRITE	0x10

#घोषणा FW_CFG_DMA_SIGNATURE    0x51454d5520434647ULL /* "QEMU CFG" */

/* Control as first field allows क्रम dअगरferent काष्ठाures selected by this
 * field, which might be useful in the future
 */
काष्ठा fw_cfg_dma_access अणु
	__be32 control;
	__be32 length;
	__be64 address;
पूर्ण;

#घोषणा FW_CFG_VMCOREINFO_खाताNAME "etc/vmcoreinfo"

#घोषणा FW_CFG_VMCOREINFO_FORMAT_NONE 0x0
#घोषणा FW_CFG_VMCOREINFO_FORMAT_ELF 0x1

काष्ठा fw_cfg_vmcoreinfo अणु
	__le16 host_क्रमmat;
	__le16 guest_क्रमmat;
	__le32 size;
	__le64 paddr;
पूर्ण;

#पूर्ण_अगर
