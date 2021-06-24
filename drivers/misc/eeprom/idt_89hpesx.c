<शैली गुरु>
/*
 *   This file is provided under a GPLv2 license.  When using or
 *   redistributing this file, you may करो so under that license.
 *
 *   GPL LICENSE SUMMARY
 *
 *   Copyright (C) 2016 T-Platक्रमms. All Rights Reserved.
 *
 *   This program is मुक्त software; you can redistribute it and/or modअगरy it
 *   under the terms and conditions of the GNU General Public License,
 *   version 2, as published by the Free Software Foundation.
 *
 *   This program is distributed in the hope that it will be useful, but WITHOUT
 *   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *   FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License क्रम
 *   more details.
 *
 *   You should have received a copy of the GNU General Public License aदीर्घ
 *   with this program; अगर not, it can be found <http://www.gnu.org/licenses/>.
 *
 *   The full GNU General Public License is included in this distribution in
 *   the file called "COPYING".
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * IDT PCIe-चयन NTB Linux driver
 *
 * Contact Inक्रमmation:
 * Serge Semin <fancer.lancer@gmail.com>, <Sergey.Semin@t-platक्रमms.ru>
 */
/*
 *           NOTE of the IDT 89HPESx SMBus-slave पूर्णांकerface driver
 *    This driver primarily is developed to have an access to EEPROM device of
 * IDT PCIe-चयनes. IDT provides a simple SMBus पूर्णांकerface to perक्रमm IO-
 * operations from/to EEPROM, which is located at निजी (so called Master)
 * SMBus of चयनes. Using that पूर्णांकerface this the driver creates a simple
 * binary sysfs-file in the device directory:
 * /sys/bus/i2c/devices/<bus>-<devaddr>/eeprom
 * In हाल अगर पढ़ो-only flag is specअगरied in the dts-node of device desription,
 * User-space applications won't be able to ग_लिखो to the EEPROM sysfs-node.
 *    Additionally IDT 89HPESx SMBus पूर्णांकerface has an ability to ग_लिखो/पढ़ो
 * data of device CSRs. This driver exposes debugf-file to perक्रमm simple IO
 * operations using that ability क्रम just basic debug purpose. Particularly
 * next file is created in the specअगरic debugfs-directory:
 * /sys/kernel/debug/idt_csr/
 * Format of the debugfs-node is:
 * $ cat /sys/kernel/debug/idt_csr/<bus>-<devaddr>/<devname>;
 * <CSR address>:<CSR value>
 * So पढ़ोing the content of the file gives current CSR address and it value.
 * If User-space application wishes to change current CSR address,
 * it can just ग_लिखो a proper value to the sysfs-file:
 * $ echo "<CSR address>" > /sys/kernel/debug/idt_csr/<bus>-<devaddr>/<devname>
 * If it wants to change the CSR value as well, the क्रमmat of the ग_लिखो
 * operation is:
 * $ echo "<CSR address>:<CSR value>" > \
 *        /sys/kernel/debug/idt_csr/<bus>-<devaddr>/<devname>;
 * CSR address and value can be any of hexadecimal, decimal or octal क्रमmat.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/sizes.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/property.h>
#समावेश <linux/i2c.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/delay.h>

#घोषणा IDT_NAME		"89hpesx"
#घोषणा IDT_89HPESX_DESC	"IDT 89HPESx SMBus-slave interface driver"
#घोषणा IDT_89HPESX_VER		"1.0"

MODULE_DESCRIPTION(IDT_89HPESX_DESC);
MODULE_VERSION(IDT_89HPESX_VER);
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("T-platforms");

/*
 * csr_dbgdir - CSR पढ़ो/ग_लिखो operations Debugfs directory
 */
अटल काष्ठा dentry *csr_dbgdir;

/*
 * काष्ठा idt_89hpesx_dev - IDT 89HPESx device data काष्ठाure
 * @eesize:	Size of EEPROM in bytes (calculated from "idt,eecompatible")
 * @eero:	EEPROM Read-only flag
 * @eeaddr:	EEPROM custom address
 *
 * @inieecmd:	Initial cmd value क्रम EEPROM पढ़ो/ग_लिखो operations
 * @inicsrcmd:	Initial cmd value क्रम CSR पढ़ो/ग_लिखो operations
 * @iniccode:	Initialial command code value क्रम IO-operations
 *
 * @csr:	CSR address to perक्रमm पढ़ो operation
 *
 * @smb_ग_लिखो:	SMBus ग_लिखो method
 * @smb_पढ़ो:	SMBus पढ़ो method
 * @smb_mtx:	SMBus mutex
 *
 * @client:	i2c client used to perक्रमm IO operations
 *
 * @ee_file:	EEPROM पढ़ो/ग_लिखो sysfs-file
 */
काष्ठा idt_smb_seq;
काष्ठा idt_89hpesx_dev अणु
	u32 eesize;
	bool eero;
	u8 eeaddr;

	u8 inieecmd;
	u8 inicsrcmd;
	u8 iniccode;

	u16 csr;

	पूर्णांक (*smb_ग_लिखो)(काष्ठा idt_89hpesx_dev *, स्थिर काष्ठा idt_smb_seq *);
	पूर्णांक (*smb_पढ़ो)(काष्ठा idt_89hpesx_dev *, काष्ठा idt_smb_seq *);
	काष्ठा mutex smb_mtx;

	काष्ठा i2c_client *client;

	काष्ठा bin_attribute *ee_file;
	काष्ठा dentry *csr_dir;
पूर्ण;

/*
 * काष्ठा idt_smb_seq - sequence of data to be पढ़ो/written from/to IDT 89HPESx
 * @ccode:	SMBus command code
 * @bytecnt:	Byte count of operation
 * @data:	Data to by written
 */
काष्ठा idt_smb_seq अणु
	u8 ccode;
	u8 bytecnt;
	u8 *data;
पूर्ण;

/*
 * काष्ठा idt_eeprom_seq - sequence of data to be पढ़ो/written from/to EEPROM
 * @cmd:	Transaction CMD
 * @eeaddr:	EEPROM custom address
 * @memaddr:	Internal memory address of EEPROM
 * @data:	Data to be written at the memory address
 */
काष्ठा idt_eeprom_seq अणु
	u8 cmd;
	u8 eeaddr;
	u16 memaddr;
	u8 data;
पूर्ण __packed;

/*
 * काष्ठा idt_csr_seq - sequence of data to be पढ़ो/written from/to CSR
 * @cmd:	Transaction CMD
 * @csraddr:	Internal IDT device CSR address
 * @data:	Data to be पढ़ो/written from/to the CSR address
 */
काष्ठा idt_csr_seq अणु
	u8 cmd;
	u16 csraddr;
	u32 data;
पूर्ण __packed;

/*
 * SMBus command code macros
 * @CCODE_END:		Indicates the end of transaction
 * @CCODE_START:	Indicates the start of transaction
 * @CCODE_CSR:		CSR पढ़ो/ग_लिखो transaction
 * @CCODE_EEPROM:	EEPROM पढ़ो/ग_लिखो transaction
 * @CCODE_BYTE:		Supplied data has BYTE length
 * @CCODE_WORD:		Supplied data has WORD length
 * @CCODE_BLOCK:	Supplied data has variable length passed in bytecnt
 *			byte right following CCODE byte
 */
#घोषणा CCODE_END	((u8)0x01)
#घोषणा CCODE_START	((u8)0x02)
#घोषणा CCODE_CSR	((u8)0x00)
#घोषणा CCODE_EEPROM	((u8)0x04)
#घोषणा CCODE_BYTE	((u8)0x00)
#घोषणा CCODE_WORD	((u8)0x20)
#घोषणा CCODE_BLOCK	((u8)0x40)
#घोषणा CCODE_PEC	((u8)0x80)

/*
 * EEPROM command macros
 * @EEPROM_OP_WRITE:	EEPROM ग_लिखो operation
 * @EEPROM_OP_READ:	EEPROM पढ़ो operation
 * @EEPROM_USA:		Use specअगरied address of EEPROM
 * @EEPROM_NAERR:	EEPROM device is not पढ़ोy to respond
 * @EEPROM_LAERR:	EEPROM arbitration loss error
 * @EEPROM_MSS:		EEPROM misplace start & stop bits error
 * @EEPROM_WR_CNT:	Bytes count to perक्रमm ग_लिखो operation
 * @EEPROM_WRRD_CNT:	Bytes count to ग_लिखो beक्रमe पढ़ोing
 * @EEPROM_RD_CNT:	Bytes count to perक्रमm पढ़ो operation
 * @EEPROM_DEF_SIZE:	Fall back size of EEPROM
 * @EEPROM_DEF_ADDR:	Defatul EEPROM address
 * @EEPROM_TOUT:	Timeout beक्रमe retry पढ़ो operation अगर eeprom is busy
 */
#घोषणा EEPROM_OP_WRITE	((u8)0x00)
#घोषणा EEPROM_OP_READ	((u8)0x01)
#घोषणा EEPROM_USA	((u8)0x02)
#घोषणा EEPROM_NAERR	((u8)0x08)
#घोषणा EEPROM_LAERR    ((u8)0x10)
#घोषणा EEPROM_MSS	((u8)0x20)
#घोषणा EEPROM_WR_CNT	((u8)5)
#घोषणा EEPROM_WRRD_CNT	((u8)4)
#घोषणा EEPROM_RD_CNT	((u8)5)
#घोषणा EEPROM_DEF_SIZE	((u16)4096)
#घोषणा EEPROM_DEF_ADDR	((u8)0x50)
#घोषणा EEPROM_TOUT	(100)

/*
 * CSR command macros
 * @CSR_DWE:		Enable all four bytes of the operation
 * @CSR_OP_WRITE:	CSR ग_लिखो operation
 * @CSR_OP_READ:	CSR पढ़ो operation
 * @CSR_RERR:		Read operation error
 * @CSR_WERR:		Write operation error
 * @CSR_WR_CNT:		Bytes count to perक्रमm ग_लिखो operation
 * @CSR_WRRD_CNT:	Bytes count to ग_लिखो beक्रमe पढ़ोing
 * @CSR_RD_CNT:		Bytes count to perक्रमm पढ़ो operation
 * @CSR_MAX:		Maximum CSR address
 * @CSR_DEF:		Default CSR address
 * @CSR_REAL_ADDR:	CSR real unshअगरted address
 */
#घोषणा CSR_DWE			((u8)0x0F)
#घोषणा CSR_OP_WRITE		((u8)0x00)
#घोषणा CSR_OP_READ		((u8)0x10)
#घोषणा CSR_RERR		((u8)0x40)
#घोषणा CSR_WERR		((u8)0x80)
#घोषणा CSR_WR_CNT		((u8)7)
#घोषणा CSR_WRRD_CNT		((u8)3)
#घोषणा CSR_RD_CNT		((u8)7)
#घोषणा CSR_MAX			((u32)0x3FFFF)
#घोषणा CSR_DEF			((u16)0x0000)
#घोषणा CSR_REAL_ADDR(val)	((अचिन्हित पूर्णांक)val << 2)

/*
 * IDT 89HPESx basic रेजिस्टर
 * @IDT_VIDDID_CSR:	PCIe VID and DID of IDT 89HPESx
 * @IDT_VID_MASK:	Mask of VID
 */
#घोषणा IDT_VIDDID_CSR	((u32)0x0000)
#घोषणा IDT_VID_MASK	((u32)0xFFFF)

/*
 * IDT 89HPESx can send NACK when new command is sent beक्रमe previous one
 * fininshed execution. In this हाल driver retries operation
 * certain बार.
 * @RETRY_CNT:		Number of retries beक्रमe giving up and fail
 * @idt_smb_safe:	Generate a retry loop on corresponding SMBus method
 */
#घोषणा RETRY_CNT (128)
#घोषणा idt_smb_safe(ops, args...) (अणु \
	पूर्णांक __retry = RETRY_CNT; \
	s32 __sts; \
	करो अणु \
		__sts = i2c_smbus_ ## ops ## _data(args); \
	पूर्ण जबतक (__retry-- && __sts < 0); \
	__sts; \
पूर्ण)

/*===========================================================================
 *                         i2c bus level IO-operations
 *===========================================================================
 */

/*
 * idt_smb_ग_लिखो_byte() - SMBus ग_लिखो method when I2C_SMBUS_BYTE_DATA operation
 *                        is only available
 * @pdev:	Poपूर्णांकer to the driver data
 * @seq:	Sequence of data to be written
 */
अटल पूर्णांक idt_smb_ग_लिखो_byte(काष्ठा idt_89hpesx_dev *pdev,
			      स्थिर काष्ठा idt_smb_seq *seq)
अणु
	s32 sts;
	u8 ccode;
	पूर्णांक idx;

	/* Loop over the supplied data sending byte one-by-one */
	क्रम (idx = 0; idx < seq->bytecnt; idx++) अणु
		/* Collect the command code byte */
		ccode = seq->ccode | CCODE_BYTE;
		अगर (idx == 0)
			ccode |= CCODE_START;
		अगर (idx == seq->bytecnt - 1)
			ccode |= CCODE_END;

		/* Send data to the device */
		sts = idt_smb_safe(ग_लिखो_byte, pdev->client, ccode,
			seq->data[idx]);
		अगर (sts != 0)
			वापस (पूर्णांक)sts;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * idt_smb_पढ़ो_byte() - SMBus पढ़ो method when I2C_SMBUS_BYTE_DATA operation
 *                        is only available
 * @pdev:	Poपूर्णांकer to the driver data
 * @seq:	Buffer to पढ़ो data to
 */
अटल पूर्णांक idt_smb_पढ़ो_byte(काष्ठा idt_89hpesx_dev *pdev,
			     काष्ठा idt_smb_seq *seq)
अणु
	s32 sts;
	u8 ccode;
	पूर्णांक idx;

	/* Loop over the supplied buffer receiving byte one-by-one */
	क्रम (idx = 0; idx < seq->bytecnt; idx++) अणु
		/* Collect the command code byte */
		ccode = seq->ccode | CCODE_BYTE;
		अगर (idx == 0)
			ccode |= CCODE_START;
		अगर (idx == seq->bytecnt - 1)
			ccode |= CCODE_END;

		/* Read data from the device */
		sts = idt_smb_safe(पढ़ो_byte, pdev->client, ccode);
		अगर (sts < 0)
			वापस (पूर्णांक)sts;

		seq->data[idx] = (u8)sts;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * idt_smb_ग_लिखो_word() - SMBus ग_लिखो method when I2C_SMBUS_BYTE_DATA and
 *                        I2C_FUNC_SMBUS_WORD_DATA operations are available
 * @pdev:	Poपूर्णांकer to the driver data
 * @seq:	Sequence of data to be written
 */
अटल पूर्णांक idt_smb_ग_लिखो_word(काष्ठा idt_89hpesx_dev *pdev,
			      स्थिर काष्ठा idt_smb_seq *seq)
अणु
	s32 sts;
	u8 ccode;
	पूर्णांक idx, evencnt;

	/* Calculate the even count of data to send */
	evencnt = seq->bytecnt - (seq->bytecnt % 2);

	/* Loop over the supplied data sending two bytes at a समय */
	क्रम (idx = 0; idx < evencnt; idx += 2) अणु
		/* Collect the command code byte */
		ccode = seq->ccode | CCODE_WORD;
		अगर (idx == 0)
			ccode |= CCODE_START;
		अगर (idx == evencnt - 2)
			ccode |= CCODE_END;

		/* Send word data to the device */
		sts = idt_smb_safe(ग_लिखो_word, pdev->client, ccode,
			*(u16 *)&seq->data[idx]);
		अगर (sts != 0)
			वापस (पूर्णांक)sts;
	पूर्ण

	/* If there is odd number of bytes then send just one last byte */
	अगर (seq->bytecnt != evencnt) अणु
		/* Collect the command code byte */
		ccode = seq->ccode | CCODE_BYTE | CCODE_END;
		अगर (idx == 0)
			ccode |= CCODE_START;

		/* Send byte data to the device */
		sts = idt_smb_safe(ग_लिखो_byte, pdev->client, ccode,
			seq->data[idx]);
		अगर (sts != 0)
			वापस (पूर्णांक)sts;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * idt_smb_पढ़ो_word() - SMBus पढ़ो method when I2C_SMBUS_BYTE_DATA and
 *                       I2C_FUNC_SMBUS_WORD_DATA operations are available
 * @pdev:	Poपूर्णांकer to the driver data
 * @seq:	Buffer to पढ़ो data to
 */
अटल पूर्णांक idt_smb_पढ़ो_word(काष्ठा idt_89hpesx_dev *pdev,
			     काष्ठा idt_smb_seq *seq)
अणु
	s32 sts;
	u8 ccode;
	पूर्णांक idx, evencnt;

	/* Calculate the even count of data to send */
	evencnt = seq->bytecnt - (seq->bytecnt % 2);

	/* Loop over the supplied data पढ़ोing two bytes at a समय */
	क्रम (idx = 0; idx < evencnt; idx += 2) अणु
		/* Collect the command code byte */
		ccode = seq->ccode | CCODE_WORD;
		अगर (idx == 0)
			ccode |= CCODE_START;
		अगर (idx == evencnt - 2)
			ccode |= CCODE_END;

		/* Read word data from the device */
		sts = idt_smb_safe(पढ़ो_word, pdev->client, ccode);
		अगर (sts < 0)
			वापस (पूर्णांक)sts;

		*(u16 *)&seq->data[idx] = (u16)sts;
	पूर्ण

	/* If there is odd number of bytes then receive just one last byte */
	अगर (seq->bytecnt != evencnt) अणु
		/* Collect the command code byte */
		ccode = seq->ccode | CCODE_BYTE | CCODE_END;
		अगर (idx == 0)
			ccode |= CCODE_START;

		/* Read last data byte from the device */
		sts = idt_smb_safe(पढ़ो_byte, pdev->client, ccode);
		अगर (sts < 0)
			वापस (पूर्णांक)sts;

		seq->data[idx] = (u8)sts;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * idt_smb_ग_लिखो_block() - SMBus ग_लिखो method when I2C_SMBUS_BLOCK_DATA
 *                         operation is available
 * @pdev:	Poपूर्णांकer to the driver data
 * @seq:	Sequence of data to be written
 */
अटल पूर्णांक idt_smb_ग_लिखो_block(काष्ठा idt_89hpesx_dev *pdev,
			       स्थिर काष्ठा idt_smb_seq *seq)
अणु
	u8 ccode;

	/* Return error अगर too much data passed to send */
	अगर (seq->bytecnt > I2C_SMBUS_BLOCK_MAX)
		वापस -EINVAL;

	/* Collect the command code byte */
	ccode = seq->ccode | CCODE_BLOCK | CCODE_START | CCODE_END;

	/* Send block of data to the device */
	वापस idt_smb_safe(ग_लिखो_block, pdev->client, ccode, seq->bytecnt,
		seq->data);
पूर्ण

/*
 * idt_smb_पढ़ो_block() - SMBus पढ़ो method when I2C_SMBUS_BLOCK_DATA
 *                        operation is available
 * @pdev:	Poपूर्णांकer to the driver data
 * @seq:	Buffer to पढ़ो data to
 */
अटल पूर्णांक idt_smb_पढ़ो_block(काष्ठा idt_89hpesx_dev *pdev,
			      काष्ठा idt_smb_seq *seq)
अणु
	s32 sts;
	u8 ccode;

	/* Return error अगर too much data passed to send */
	अगर (seq->bytecnt > I2C_SMBUS_BLOCK_MAX)
		वापस -EINVAL;

	/* Collect the command code byte */
	ccode = seq->ccode | CCODE_BLOCK | CCODE_START | CCODE_END;

	/* Read block of data from the device */
	sts = idt_smb_safe(पढ़ो_block, pdev->client, ccode, seq->data);
	अगर (sts != seq->bytecnt)
		वापस (sts < 0 ? sts : -ENODATA);

	वापस 0;
पूर्ण

/*
 * idt_smb_ग_लिखो_i2c_block() - SMBus ग_लिखो method when I2C_SMBUS_I2C_BLOCK_DATA
 *                             operation is available
 * @pdev:	Poपूर्णांकer to the driver data
 * @seq:	Sequence of data to be written
 *
 * NOTE It's usual SMBus ग_लिखो block operation, except the actual data length is
 * sent as first byte of data
 */
अटल पूर्णांक idt_smb_ग_लिखो_i2c_block(काष्ठा idt_89hpesx_dev *pdev,
				   स्थिर काष्ठा idt_smb_seq *seq)
अणु
	u8 ccode, buf[I2C_SMBUS_BLOCK_MAX + 1];

	/* Return error अगर too much data passed to send */
	अगर (seq->bytecnt > I2C_SMBUS_BLOCK_MAX)
		वापस -EINVAL;

	/* Collect the data to send. Length byte must be added prior the data */
	buf[0] = seq->bytecnt;
	स_नकल(&buf[1], seq->data, seq->bytecnt);

	/* Collect the command code byte */
	ccode = seq->ccode | CCODE_BLOCK | CCODE_START | CCODE_END;

	/* Send length and block of data to the device */
	वापस idt_smb_safe(ग_लिखो_i2c_block, pdev->client, ccode,
		seq->bytecnt + 1, buf);
पूर्ण

/*
 * idt_smb_पढ़ो_i2c_block() - SMBus पढ़ो method when I2C_SMBUS_I2C_BLOCK_DATA
 *                            operation is available
 * @pdev:	Poपूर्णांकer to the driver data
 * @seq:	Buffer to पढ़ो data to
 *
 * NOTE It's usual SMBus पढ़ो block operation, except the actual data length is
 * retrieved as first byte of data
 */
अटल पूर्णांक idt_smb_पढ़ो_i2c_block(काष्ठा idt_89hpesx_dev *pdev,
				  काष्ठा idt_smb_seq *seq)
अणु
	u8 ccode, buf[I2C_SMBUS_BLOCK_MAX + 1];
	s32 sts;

	/* Return error अगर too much data passed to send */
	अगर (seq->bytecnt > I2C_SMBUS_BLOCK_MAX)
		वापस -EINVAL;

	/* Collect the command code byte */
	ccode = seq->ccode | CCODE_BLOCK | CCODE_START | CCODE_END;

	/* Read length and block of data from the device */
	sts = idt_smb_safe(पढ़ो_i2c_block, pdev->client, ccode,
		seq->bytecnt + 1, buf);
	अगर (sts != seq->bytecnt + 1)
		वापस (sts < 0 ? sts : -ENODATA);
	अगर (buf[0] != seq->bytecnt)
		वापस -ENODATA;

	/* Copy retrieved data to the output data buffer */
	स_नकल(seq->data, &buf[1], seq->bytecnt);

	वापस 0;
पूर्ण

/*===========================================================================
 *                          EEPROM IO-operations
 *===========================================================================
 */

/*
 * idt_eeprom_पढ़ो_byte() - पढ़ो just one byte from EEPROM
 * @pdev:	Poपूर्णांकer to the driver data
 * @memaddr:	Start EEPROM memory address
 * @data:	Data to be written to EEPROM
 */
अटल पूर्णांक idt_eeprom_पढ़ो_byte(काष्ठा idt_89hpesx_dev *pdev, u16 memaddr,
				u8 *data)
अणु
	काष्ठा device *dev = &pdev->client->dev;
	काष्ठा idt_eeprom_seq eeseq;
	काष्ठा idt_smb_seq smbseq;
	पूर्णांक ret, retry;

	/* Initialize SMBus sequence fields */
	smbseq.ccode = pdev->iniccode | CCODE_EEPROM;
	smbseq.data = (u8 *)&eeseq;

	/*
	 * Someबार EEPROM may respond with NACK अगर it's busy with previous
	 * operation, so we need to perक्रमm a few attempts of पढ़ो cycle
	 */
	retry = RETRY_CNT;
	करो अणु
		/* Send EEPROM memory address to पढ़ो data from */
		smbseq.bytecnt = EEPROM_WRRD_CNT;
		eeseq.cmd = pdev->inieecmd | EEPROM_OP_READ;
		eeseq.eeaddr = pdev->eeaddr;
		eeseq.memaddr = cpu_to_le16(memaddr);
		ret = pdev->smb_ग_लिखो(pdev, &smbseq);
		अगर (ret != 0) अणु
			dev_err(dev, "Failed to init eeprom addr 0x%02hhx",
				memaddr);
			अवरोध;
		पूर्ण

		/* Perक्रमm पढ़ो operation */
		smbseq.bytecnt = EEPROM_RD_CNT;
		ret = pdev->smb_पढ़ो(pdev, &smbseq);
		अगर (ret != 0) अणु
			dev_err(dev, "Failed to read eeprom data 0x%02hhx",
				memaddr);
			अवरोध;
		पूर्ण

		/* Restart पढ़ो operation अगर the device is busy */
		अगर (retry && (eeseq.cmd & EEPROM_NAERR)) अणु
			dev_dbg(dev, "EEPROM busy, retry reading after %d ms",
				EEPROM_TOUT);
			msleep(EEPROM_TOUT);
			जारी;
		पूर्ण

		/* Check whether IDT successfully पढ़ो data from EEPROM */
		अगर (eeseq.cmd & (EEPROM_NAERR | EEPROM_LAERR | EEPROM_MSS)) अणु
			dev_err(dev,
				"Communication with eeprom failed, cmd 0x%hhx",
				eeseq.cmd);
			ret = -EREMOTEIO;
			अवरोध;
		पूर्ण

		/* Save retrieved data and निकास the loop */
		*data = eeseq.data;
		अवरोध;
	पूर्ण जबतक (retry--);

	/* Return the status of operation */
	वापस ret;
पूर्ण

/*
 * idt_eeprom_ग_लिखो() - EEPROM ग_लिखो operation
 * @pdev:	Poपूर्णांकer to the driver data
 * @memaddr:	Start EEPROM memory address
 * @len:	Length of data to be written
 * @data:	Data to be written to EEPROM
 */
अटल पूर्णांक idt_eeprom_ग_लिखो(काष्ठा idt_89hpesx_dev *pdev, u16 memaddr, u16 len,
			    स्थिर u8 *data)
अणु
	काष्ठा device *dev = &pdev->client->dev;
	काष्ठा idt_eeprom_seq eeseq;
	काष्ठा idt_smb_seq smbseq;
	पूर्णांक ret;
	u16 idx;

	/* Initialize SMBus sequence fields */
	smbseq.ccode = pdev->iniccode | CCODE_EEPROM;
	smbseq.data = (u8 *)&eeseq;

	/* Send data byte-by-byte, checking अगर it is successfully written */
	क्रम (idx = 0; idx < len; idx++, memaddr++) अणु
		/* Lock IDT SMBus device */
		mutex_lock(&pdev->smb_mtx);

		/* Perक्रमm ग_लिखो operation */
		smbseq.bytecnt = EEPROM_WR_CNT;
		eeseq.cmd = pdev->inieecmd | EEPROM_OP_WRITE;
		eeseq.eeaddr = pdev->eeaddr;
		eeseq.memaddr = cpu_to_le16(memaddr);
		eeseq.data = data[idx];
		ret = pdev->smb_ग_लिखो(pdev, &smbseq);
		अगर (ret != 0) अणु
			dev_err(dev,
				"Failed to write 0x%04hx:0x%02hhx to eeprom",
				memaddr, data[idx]);
			जाओ err_mutex_unlock;
		पूर्ण

		/*
		 * Check whether the data is successfully written by पढ़ोing
		 * from the same EEPROM memory address.
		 */
		eeseq.data = ~data[idx];
		ret = idt_eeprom_पढ़ो_byte(pdev, memaddr, &eeseq.data);
		अगर (ret != 0)
			जाओ err_mutex_unlock;

		/* Check whether the पढ़ो byte is the same as written one */
		अगर (eeseq.data != data[idx]) अणु
			dev_err(dev, "Values don't match 0x%02hhx != 0x%02hhx",
				eeseq.data, data[idx]);
			ret = -EREMOTEIO;
			जाओ err_mutex_unlock;
		पूर्ण

		/* Unlock IDT SMBus device */
err_mutex_unlock:
		mutex_unlock(&pdev->smb_mtx);
		अगर (ret != 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * idt_eeprom_पढ़ो() - EEPROM पढ़ो operation
 * @pdev:	Poपूर्णांकer to the driver data
 * @memaddr:	Start EEPROM memory address
 * @len:	Length of data to पढ़ो
 * @buf:	Buffer to पढ़ो data to
 */
अटल पूर्णांक idt_eeprom_पढ़ो(काष्ठा idt_89hpesx_dev *pdev, u16 memaddr, u16 len,
			   u8 *buf)
अणु
	पूर्णांक ret;
	u16 idx;

	/* Read data byte-by-byte, retrying अगर it wasn't successful */
	क्रम (idx = 0; idx < len; idx++, memaddr++) अणु
		/* Lock IDT SMBus device */
		mutex_lock(&pdev->smb_mtx);

		/* Just पढ़ो the byte to the buffer */
		ret = idt_eeprom_पढ़ो_byte(pdev, memaddr, &buf[idx]);

		/* Unlock IDT SMBus device */
		mutex_unlock(&pdev->smb_mtx);

		/* Return error अगर पढ़ो operation failed */
		अगर (ret != 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*===========================================================================
 *                          CSR IO-operations
 *===========================================================================
 */

/*
 * idt_csr_ग_लिखो() - CSR ग_लिखो operation
 * @pdev:	Poपूर्णांकer to the driver data
 * @csraddr:	CSR address (with no two LS bits)
 * @data:	Data to be written to CSR
 */
अटल पूर्णांक idt_csr_ग_लिखो(काष्ठा idt_89hpesx_dev *pdev, u16 csraddr,
			 स्थिर u32 data)
अणु
	काष्ठा device *dev = &pdev->client->dev;
	काष्ठा idt_csr_seq csrseq;
	काष्ठा idt_smb_seq smbseq;
	पूर्णांक ret;

	/* Initialize SMBus sequence fields */
	smbseq.ccode = pdev->iniccode | CCODE_CSR;
	smbseq.data = (u8 *)&csrseq;

	/* Lock IDT SMBus device */
	mutex_lock(&pdev->smb_mtx);

	/* Perक्रमm ग_लिखो operation */
	smbseq.bytecnt = CSR_WR_CNT;
	csrseq.cmd = pdev->inicsrcmd | CSR_OP_WRITE;
	csrseq.csraddr = cpu_to_le16(csraddr);
	csrseq.data = cpu_to_le32(data);
	ret = pdev->smb_ग_लिखो(pdev, &smbseq);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to write 0x%04x: 0x%04x to csr",
			CSR_REAL_ADDR(csraddr), data);
		जाओ err_mutex_unlock;
	पूर्ण

	/* Send CSR address to पढ़ो data from */
	smbseq.bytecnt = CSR_WRRD_CNT;
	csrseq.cmd = pdev->inicsrcmd | CSR_OP_READ;
	ret = pdev->smb_ग_लिखो(pdev, &smbseq);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to init csr address 0x%04x",
			CSR_REAL_ADDR(csraddr));
		जाओ err_mutex_unlock;
	पूर्ण

	/* Perक्रमm पढ़ो operation */
	smbseq.bytecnt = CSR_RD_CNT;
	ret = pdev->smb_पढ़ो(pdev, &smbseq);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to read csr 0x%04x",
			CSR_REAL_ADDR(csraddr));
		जाओ err_mutex_unlock;
	पूर्ण

	/* Check whether IDT successfully retrieved CSR data */
	अगर (csrseq.cmd & (CSR_RERR | CSR_WERR)) अणु
		dev_err(dev, "IDT failed to perform CSR r/w");
		ret = -EREMOTEIO;
		जाओ err_mutex_unlock;
	पूर्ण

	/* Unlock IDT SMBus device */
err_mutex_unlock:
	mutex_unlock(&pdev->smb_mtx);

	वापस ret;
पूर्ण

/*
 * idt_csr_पढ़ो() - CSR पढ़ो operation
 * @pdev:	Poपूर्णांकer to the driver data
 * @csraddr:	CSR address (with no two LS bits)
 * @data:	Data to be written to CSR
 */
अटल पूर्णांक idt_csr_पढ़ो(काष्ठा idt_89hpesx_dev *pdev, u16 csraddr, u32 *data)
अणु
	काष्ठा device *dev = &pdev->client->dev;
	काष्ठा idt_csr_seq csrseq;
	काष्ठा idt_smb_seq smbseq;
	पूर्णांक ret;

	/* Initialize SMBus sequence fields */
	smbseq.ccode = pdev->iniccode | CCODE_CSR;
	smbseq.data = (u8 *)&csrseq;

	/* Lock IDT SMBus device */
	mutex_lock(&pdev->smb_mtx);

	/* Send CSR रेजिस्टर address beक्रमe पढ़ोing it */
	smbseq.bytecnt = CSR_WRRD_CNT;
	csrseq.cmd = pdev->inicsrcmd | CSR_OP_READ;
	csrseq.csraddr = cpu_to_le16(csraddr);
	ret = pdev->smb_ग_लिखो(pdev, &smbseq);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to init csr address 0x%04x",
			CSR_REAL_ADDR(csraddr));
		जाओ err_mutex_unlock;
	पूर्ण

	/* Perक्रमm पढ़ो operation */
	smbseq.bytecnt = CSR_RD_CNT;
	ret = pdev->smb_पढ़ो(pdev, &smbseq);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to read csr 0x%04hx",
			CSR_REAL_ADDR(csraddr));
		जाओ err_mutex_unlock;
	पूर्ण

	/* Check whether IDT successfully retrieved CSR data */
	अगर (csrseq.cmd & (CSR_RERR | CSR_WERR)) अणु
		dev_err(dev, "IDT failed to perform CSR r/w");
		ret = -EREMOTEIO;
		जाओ err_mutex_unlock;
	पूर्ण

	/* Save data retrieved from IDT */
	*data = le32_to_cpu(csrseq.data);

	/* Unlock IDT SMBus device */
err_mutex_unlock:
	mutex_unlock(&pdev->smb_mtx);

	वापस ret;
पूर्ण

/*===========================================================================
 *                          Sysfs/debugfs-nodes IO-operations
 *===========================================================================
 */

/*
 * eeprom_ग_लिखो() - EEPROM sysfs-node ग_लिखो callback
 * @filep:	Poपूर्णांकer to the file प्रणाली node
 * @kobj:	Poपूर्णांकer to the kernel object related to the sysfs-node
 * @attr:	Attributes of the file
 * @buf:	Buffer to ग_लिखो data to
 * @off:	Offset at which data should be written to
 * @count:	Number of bytes to ग_लिखो
 */
अटल sमाप_प्रकार eeprom_ग_लिखो(काष्ठा file *filp, काष्ठा kobject *kobj,
			    काष्ठा bin_attribute *attr,
			    अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा idt_89hpesx_dev *pdev;
	पूर्णांक ret;

	/* Retrieve driver data */
	pdev = dev_get_drvdata(kobj_to_dev(kobj));

	/* Perक्रमm EEPROM ग_लिखो operation */
	ret = idt_eeprom_ग_लिखो(pdev, (u16)off, (u16)count, (u8 *)buf);
	वापस (ret != 0 ? ret : count);
पूर्ण

/*
 * eeprom_पढ़ो() - EEPROM sysfs-node पढ़ो callback
 * @filep:	Poपूर्णांकer to the file प्रणाली node
 * @kobj:	Poपूर्णांकer to the kernel object related to the sysfs-node
 * @attr:	Attributes of the file
 * @buf:	Buffer to ग_लिखो data to
 * @off:	Offset at which data should be written to
 * @count:	Number of bytes to ग_लिखो
 */
अटल sमाप_प्रकार eeprom_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
			   काष्ठा bin_attribute *attr,
			   अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा idt_89hpesx_dev *pdev;
	पूर्णांक ret;

	/* Retrieve driver data */
	pdev = dev_get_drvdata(kobj_to_dev(kobj));

	/* Perक्रमm EEPROM पढ़ो operation */
	ret = idt_eeprom_पढ़ो(pdev, (u16)off, (u16)count, (u8 *)buf);
	वापस (ret != 0 ? ret : count);
पूर्ण

/*
 * idt_dbgfs_csr_ग_लिखो() - CSR debugfs-node ग_लिखो callback
 * @filep:	Poपूर्णांकer to the file प्रणाली file descriptor
 * @buf:	Buffer to पढ़ो data from
 * @count:	Size of the buffer
 * @offp:	Offset within the file
 *
 * It accepts either "0x<reg addr>:0x<value>" क्रम saving रेजिस्टर address
 * and writing value to specअगरied DWORD रेजिस्टर or "0x<reg addr>" क्रम
 * just saving रेजिस्टर address in order to perक्रमm next पढ़ो operation.
 *
 * WARNING No spaces are allowed. Incoming string must be strictly क्रमmated as:
 * "<reg addr>:<value>". Register address must be aligned within 4 bytes
 * (one DWORD).
 */
अटल sमाप_प्रकार idt_dbgfs_csr_ग_लिखो(काष्ठा file *filep, स्थिर अक्षर __user *ubuf,
				   माप_प्रकार count, loff_t *offp)
अणु
	काष्ठा idt_89hpesx_dev *pdev = filep->निजी_data;
	अक्षर *colon_ch, *csraddr_str, *csrval_str;
	पूर्णांक ret, csraddr_len;
	u32 csraddr, csrval;
	अक्षर *buf;

	/* Copy data from User-space */
	buf = kदो_स्मृति(count + 1, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	ret = simple_ग_लिखो_to_buffer(buf, count, offp, ubuf, count);
	अगर (ret < 0)
		जाओ मुक्त_buf;
	buf[count] = 0;

	/* Find position of colon in the buffer */
	colon_ch = strnchr(buf, count, ':');

	/*
	 * If there is colon passed then new CSR value should be parsed as
	 * well, so allocate buffer क्रम CSR address substring.
	 * If no colon is found, then string must have just one number with
	 * no new CSR value
	 */
	अगर (colon_ch != शून्य) अणु
		csraddr_len = colon_ch - buf;
		csraddr_str =
			kदो_स्मृति(csraddr_len + 1, GFP_KERNEL);
		अगर (csraddr_str == शून्य) अणु
			ret = -ENOMEM;
			जाओ मुक्त_buf;
		पूर्ण
		/* Copy the रेजिस्टर address to the substring buffer */
		म_नकलन(csraddr_str, buf, csraddr_len);
		csraddr_str[csraddr_len] = '\0';
		/* Register value must follow the colon */
		csrval_str = colon_ch + 1;
	पूर्ण अन्यथा /* अगर (str_colon == शून्य) */ अणु
		csraddr_str = (अक्षर *)buf; /* Just to shut warning up */
		csraddr_len = strnlen(csraddr_str, count);
		csrval_str = शून्य;
	पूर्ण

	/* Convert CSR address to u32 value */
	ret = kstrtou32(csraddr_str, 0, &csraddr);
	अगर (ret != 0)
		जाओ मुक्त_csraddr_str;

	/* Check whether passed रेजिस्टर address is valid */
	अगर (csraddr > CSR_MAX || !IS_ALIGNED(csraddr, SZ_4)) अणु
		ret = -EINVAL;
		जाओ मुक्त_csraddr_str;
	पूर्ण

	/* Shअगरt रेजिस्टर address to the right so to have u16 address */
	pdev->csr = (csraddr >> 2);

	/* Parse new CSR value and send it to IDT, अगर colon has been found */
	अगर (colon_ch != शून्य) अणु
		ret = kstrtou32(csrval_str, 0, &csrval);
		अगर (ret != 0)
			जाओ मुक्त_csraddr_str;

		ret = idt_csr_ग_लिखो(pdev, pdev->csr, csrval);
		अगर (ret != 0)
			जाओ मुक्त_csraddr_str;
	पूर्ण

	/* Free memory only अगर colon has been found */
मुक्त_csraddr_str:
	अगर (colon_ch != शून्य)
		kमुक्त(csraddr_str);

	/* Free buffer allocated क्रम data retrieved from User-space */
मुक्त_buf:
	kमुक्त(buf);

	वापस (ret != 0 ? ret : count);
पूर्ण

/*
 * idt_dbgfs_csr_पढ़ो() - CSR debugfs-node पढ़ो callback
 * @filep:	Poपूर्णांकer to the file प्रणाली file descriptor
 * @buf:	Buffer to ग_लिखो data to
 * @count:	Size of the buffer
 * @offp:	Offset within the file
 *
 * It just prपूर्णांकs the pair "0x<reg addr>:0x<value>" to passed buffer.
 */
#घोषणा CSRBUF_SIZE	((माप_प्रकार)32)
अटल sमाप_प्रकार idt_dbgfs_csr_पढ़ो(काष्ठा file *filep, अक्षर __user *ubuf,
				  माप_प्रकार count, loff_t *offp)
अणु
	काष्ठा idt_89hpesx_dev *pdev = filep->निजी_data;
	u32 csraddr, csrval;
	अक्षर buf[CSRBUF_SIZE];
	पूर्णांक ret, size;

	/* Perक्रमm CSR पढ़ो operation */
	ret = idt_csr_पढ़ो(pdev, pdev->csr, &csrval);
	अगर (ret != 0)
		वापस ret;

	/* Shअगरt रेजिस्टर address to the left so to have real address */
	csraddr = ((u32)pdev->csr << 2);

	/* Prपूर्णांक the "0x<reg addr>:0x<value>" to buffer */
	size = snम_लिखो(buf, CSRBUF_SIZE, "0x%05x:0x%08x\n",
		(अचिन्हित पूर्णांक)csraddr, (अचिन्हित पूर्णांक)csrval);

	/* Copy data to User-space */
	वापस simple_पढ़ो_from_buffer(ubuf, count, offp, buf, size);
पूर्ण

/*
 * eeprom_attribute - EEPROM sysfs-node attributes
 *
 * NOTE Size will be changed in compliance with OF node. EEPROM attribute will
 * be पढ़ो-only as well अगर the corresponding flag is specअगरied in OF node.
 */
अटल BIN_ATTR_RW(eeprom, EEPROM_DEF_SIZE);

/*
 * csr_dbgfs_ops - CSR debugfs-node पढ़ो/ग_लिखो operations
 */
अटल स्थिर काष्ठा file_operations csr_dbgfs_ops = अणु
	.owner = THIS_MODULE,
	.खोलो = simple_खोलो,
	.ग_लिखो = idt_dbgfs_csr_ग_लिखो,
	.पढ़ो = idt_dbgfs_csr_पढ़ो
पूर्ण;

/*===========================================================================
 *                       Driver init/deinit methods
 *===========================================================================
 */

/*
 * idt_set_defval() - disable EEPROM access by शेष
 * @pdev:	Poपूर्णांकer to the driver data
 */
अटल व्योम idt_set_defval(काष्ठा idt_89hpesx_dev *pdev)
अणु
	/* If OF info is missing then use next values */
	pdev->eesize = 0;
	pdev->eero = true;
	pdev->inieecmd = 0;
	pdev->eeaddr = 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ee_ids[];

/*
 * idt_ee_match_id() - check whether the node beदीर्घs to compatible EEPROMs
 */
अटल स्थिर काष्ठा i2c_device_id *idt_ee_match_id(काष्ठा fwnode_handle *fwnode)
अणु
	स्थिर काष्ठा i2c_device_id *id = ee_ids;
	स्थिर अक्षर *compatible, *p;
	अक्षर devname[I2C_NAME_SIZE];
	पूर्णांक ret;

	ret = fwnode_property_पढ़ो_string(fwnode, "compatible", &compatible);
	अगर (ret)
		वापस शून्य;

	p = म_अक्षर(compatible, ',');
	strlcpy(devname, p ? p + 1 : compatible, माप(devname));
	/* Search through the device name */
	जबतक (id->name[0]) अणु
		अगर (म_भेद(devname, id->name) == 0)
			वापस id;
		id++;
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * idt_get_fw_data() - get IDT i2c-device parameters from device tree
 * @pdev:	Poपूर्णांकer to the driver data
 */
अटल व्योम idt_get_fw_data(काष्ठा idt_89hpesx_dev *pdev)
अणु
	काष्ठा device *dev = &pdev->client->dev;
	काष्ठा fwnode_handle *fwnode;
	स्थिर काष्ठा i2c_device_id *ee_id = शून्य;
	u32 eeprom_addr;
	पूर्णांक ret;

	device_क्रम_each_child_node(dev, fwnode) अणु
		ee_id = idt_ee_match_id(fwnode);
		अगर (!ee_id) अणु
			dev_warn(dev, "Skip unsupported EEPROM device");
			जारी;
		पूर्ण अन्यथा
			अवरोध;
	पूर्ण

	/* If there is no fwnode EEPROM device, then set zero size */
	अगर (!ee_id) अणु
		dev_warn(dev, "No fwnode, EEPROM access disabled");
		idt_set_defval(pdev);
		वापस;
	पूर्ण

	/* Retrieve EEPROM size */
	pdev->eesize = (u32)ee_id->driver_data;

	/* Get custom EEPROM address from 'reg' attribute */
	ret = fwnode_property_पढ़ो_u32(fwnode, "reg", &eeprom_addr);
	अगर (ret || (eeprom_addr == 0)) अणु
		dev_warn(dev, "No EEPROM reg found, use default address 0x%x",
			 EEPROM_DEF_ADDR);
		pdev->inieecmd = 0;
		pdev->eeaddr = EEPROM_DEF_ADDR << 1;
	पूर्ण अन्यथा अणु
		pdev->inieecmd = EEPROM_USA;
		pdev->eeaddr = eeprom_addr << 1;
	पूर्ण

	/* Check EEPROM 'read-only' flag */
	अगर (fwnode_property_पढ़ो_bool(fwnode, "read-only"))
		pdev->eero = true;
	अन्यथा /* अगर (!fwnode_property_पढ़ो_bool(node, "read-only")) */
		pdev->eero = false;

	dev_info(dev, "EEPROM of %d bytes found by 0x%x",
		pdev->eesize, pdev->eeaddr);
पूर्ण

/*
 * idt_create_pdev() - create and init data काष्ठाure of the driver
 * @client:	i2c client of IDT PCIe-चयन device
 */
अटल काष्ठा idt_89hpesx_dev *idt_create_pdev(काष्ठा i2c_client *client)
अणु
	काष्ठा idt_89hpesx_dev *pdev;

	/* Allocate memory क्रम driver data */
	pdev = devm_kदो_स्मृति(&client->dev, माप(काष्ठा idt_89hpesx_dev),
		GFP_KERNEL);
	अगर (pdev == शून्य)
		वापस ERR_PTR(-ENOMEM);

	/* Initialize basic fields of the data */
	pdev->client = client;
	i2c_set_clientdata(client, pdev);

	/* Read firmware nodes inक्रमmation */
	idt_get_fw_data(pdev);

	/* Initialize basic CSR CMD field - use full DWORD-sized r/w ops */
	pdev->inicsrcmd = CSR_DWE;
	pdev->csr = CSR_DEF;

	/* Enable Packet Error Checking अगर it's supported by adapter */
	अगर (i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_PEC)) अणु
		pdev->iniccode = CCODE_PEC;
		client->flags |= I2C_CLIENT_PEC;
	पूर्ण अन्यथा /* PEC is unsupported */ अणु
		pdev->iniccode = 0;
	पूर्ण

	वापस pdev;
पूर्ण

/*
 * idt_मुक्त_pdev() - मुक्त data काष्ठाure of the driver
 * @pdev:	Poपूर्णांकer to the driver data
 */
अटल व्योम idt_मुक्त_pdev(काष्ठा idt_89hpesx_dev *pdev)
अणु
	/* Clear driver data from device निजी field */
	i2c_set_clientdata(pdev->client, शून्य);
पूर्ण

/*
 * idt_set_smbus_ops() - set supported SMBus operations
 * @pdev:	Poपूर्णांकer to the driver data
 * Return status of smbus check operations
 */
अटल पूर्णांक idt_set_smbus_ops(काष्ठा idt_89hpesx_dev *pdev)
अणु
	काष्ठा i2c_adapter *adapter = pdev->client->adapter;
	काष्ठा device *dev = &pdev->client->dev;

	/* Check i2c adapter पढ़ो functionality */
	अगर (i2c_check_functionality(adapter,
				    I2C_FUNC_SMBUS_READ_BLOCK_DATA)) अणु
		pdev->smb_पढ़ो = idt_smb_पढ़ो_block;
		dev_dbg(dev, "SMBus block-read op chosen");
	पूर्ण अन्यथा अगर (i2c_check_functionality(adapter,
					   I2C_FUNC_SMBUS_READ_I2C_BLOCK)) अणु
		pdev->smb_पढ़ो = idt_smb_पढ़ो_i2c_block;
		dev_dbg(dev, "SMBus i2c-block-read op chosen");
	पूर्ण अन्यथा अगर (i2c_check_functionality(adapter,
					   I2C_FUNC_SMBUS_READ_WORD_DATA) &&
		   i2c_check_functionality(adapter,
					   I2C_FUNC_SMBUS_READ_BYTE_DATA)) अणु
		pdev->smb_पढ़ो = idt_smb_पढ़ो_word;
		dev_warn(dev, "Use slow word/byte SMBus read ops");
	पूर्ण अन्यथा अगर (i2c_check_functionality(adapter,
					   I2C_FUNC_SMBUS_READ_BYTE_DATA)) अणु
		pdev->smb_पढ़ो = idt_smb_पढ़ो_byte;
		dev_warn(dev, "Use slow byte SMBus read op");
	पूर्ण अन्यथा /* no supported smbus पढ़ो operations */ अणु
		dev_err(dev, "No supported SMBus read op");
		वापस -EPFNOSUPPORT;
	पूर्ण

	/* Check i2c adapter ग_लिखो functionality */
	अगर (i2c_check_functionality(adapter,
				    I2C_FUNC_SMBUS_WRITE_BLOCK_DATA)) अणु
		pdev->smb_ग_लिखो = idt_smb_ग_लिखो_block;
		dev_dbg(dev, "SMBus block-write op chosen");
	पूर्ण अन्यथा अगर (i2c_check_functionality(adapter,
					   I2C_FUNC_SMBUS_WRITE_I2C_BLOCK)) अणु
		pdev->smb_ग_लिखो = idt_smb_ग_लिखो_i2c_block;
		dev_dbg(dev, "SMBus i2c-block-write op chosen");
	पूर्ण अन्यथा अगर (i2c_check_functionality(adapter,
					   I2C_FUNC_SMBUS_WRITE_WORD_DATA) &&
		   i2c_check_functionality(adapter,
					   I2C_FUNC_SMBUS_WRITE_BYTE_DATA)) अणु
		pdev->smb_ग_लिखो = idt_smb_ग_लिखो_word;
		dev_warn(dev, "Use slow word/byte SMBus write op");
	पूर्ण अन्यथा अगर (i2c_check_functionality(adapter,
					   I2C_FUNC_SMBUS_WRITE_BYTE_DATA)) अणु
		pdev->smb_ग_लिखो = idt_smb_ग_लिखो_byte;
		dev_warn(dev, "Use slow byte SMBus write op");
	पूर्ण अन्यथा /* no supported smbus ग_लिखो operations */ अणु
		dev_err(dev, "No supported SMBus write op");
		वापस -EPFNOSUPPORT;
	पूर्ण

	/* Initialize IDT SMBus slave पूर्णांकerface mutex */
	mutex_init(&pdev->smb_mtx);

	वापस 0;
पूर्ण

/*
 * idt_check_dev() - check whether it's really IDT 89HPESx device
 * @pdev:	Poपूर्णांकer to the driver data
 * Return status of i2c adapter check operation
 */
अटल पूर्णांक idt_check_dev(काष्ठा idt_89hpesx_dev *pdev)
अणु
	काष्ठा device *dev = &pdev->client->dev;
	u32 viddid;
	पूर्णांक ret;

	/* Read VID and DID directly from IDT memory space */
	ret = idt_csr_पढ़ो(pdev, IDT_VIDDID_CSR, &viddid);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to read VID/DID");
		वापस ret;
	पूर्ण

	/* Check whether it's IDT device */
	अगर ((viddid & IDT_VID_MASK) != PCI_VENDOR_ID_IDT) अणु
		dev_err(dev, "Got unsupported VID/DID: 0x%08x", viddid);
		वापस -ENODEV;
	पूर्ण

	dev_info(dev, "Found IDT 89HPES device VID:0x%04x, DID:0x%04x",
		(viddid & IDT_VID_MASK), (viddid >> 16));

	वापस 0;
पूर्ण

/*
 * idt_create_sysfs_files() - create sysfs attribute files
 * @pdev:	Poपूर्णांकer to the driver data
 * Return status of operation
 */
अटल पूर्णांक idt_create_sysfs_files(काष्ठा idt_89hpesx_dev *pdev)
अणु
	काष्ठा device *dev = &pdev->client->dev;
	पूर्णांक ret;

	/* Don't do anything if EEPROM isn't accessible */
	अगर (pdev->eesize == 0) अणु
		dev_dbg(dev, "Skip creating sysfs-files");
		वापस 0;
	पूर्ण

	/* Allocate memory क्रम attribute file */
	pdev->ee_file = devm_kदो_स्मृति(dev, माप(*pdev->ee_file), GFP_KERNEL);
	अगर (!pdev->ee_file)
		वापस -ENOMEM;

	/* Copy the declared EEPROM attr काष्ठाure to change some of fields */
	स_नकल(pdev->ee_file, &bin_attr_eeprom, माप(*pdev->ee_file));

	/* In हाल of पढ़ो-only EEPROM get rid of ग_लिखो ability */
	अगर (pdev->eero) अणु
		pdev->ee_file->attr.mode &= ~0200;
		pdev->ee_file->ग_लिखो = शून्य;
	पूर्ण
	/* Create EEPROM sysfs file */
	pdev->ee_file->size = pdev->eesize;
	ret = sysfs_create_bin_file(&dev->kobj, pdev->ee_file);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to create EEPROM sysfs-node");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * idt_हटाओ_sysfs_files() - हटाओ sysfs attribute files
 * @pdev:	Poपूर्णांकer to the driver data
 */
अटल व्योम idt_हटाओ_sysfs_files(काष्ठा idt_89hpesx_dev *pdev)
अणु
	काष्ठा device *dev = &pdev->client->dev;

	/* Don't do anything if EEPROM wasn't accessible */
	अगर (pdev->eesize == 0)
		वापस;

	/* Remove EEPROM sysfs file */
	sysfs_हटाओ_bin_file(&dev->kobj, pdev->ee_file);
पूर्ण

/*
 * idt_create_dbgfs_files() - create debugfs files
 * @pdev:	Poपूर्णांकer to the driver data
 */
#घोषणा CSRNAME_LEN	((माप_प्रकार)32)
अटल व्योम idt_create_dbgfs_files(काष्ठा idt_89hpesx_dev *pdev)
अणु
	काष्ठा i2c_client *cli = pdev->client;
	अक्षर fname[CSRNAME_LEN];

	/* Create Debugfs directory क्रम CSR file */
	snम_लिखो(fname, CSRNAME_LEN, "%d-%04hx", cli->adapter->nr, cli->addr);
	pdev->csr_dir = debugfs_create_dir(fname, csr_dbgdir);

	/* Create Debugfs file क्रम CSR पढ़ो/ग_लिखो operations */
	debugfs_create_file(cli->name, 0600, pdev->csr_dir, pdev,
			    &csr_dbgfs_ops);
पूर्ण

/*
 * idt_हटाओ_dbgfs_files() - हटाओ debugfs files
 * @pdev:	Poपूर्णांकer to the driver data
 */
अटल व्योम idt_हटाओ_dbgfs_files(काष्ठा idt_89hpesx_dev *pdev)
अणु
	/* Remove CSR directory and it sysfs-node */
	debugfs_हटाओ_recursive(pdev->csr_dir);
पूर्ण

/*
 * idt_probe() - IDT 89HPESx driver probe() callback method
 */
अटल पूर्णांक idt_probe(काष्ठा i2c_client *client, स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा idt_89hpesx_dev *pdev;
	पूर्णांक ret;

	/* Create driver data */
	pdev = idt_create_pdev(client);
	अगर (IS_ERR(pdev))
		वापस PTR_ERR(pdev);

	/* Set SMBus operations */
	ret = idt_set_smbus_ops(pdev);
	अगर (ret != 0)
		जाओ err_मुक्त_pdev;

	/* Check whether it is truly IDT 89HPESx device */
	ret = idt_check_dev(pdev);
	अगर (ret != 0)
		जाओ err_मुक्त_pdev;

	/* Create sysfs files */
	ret = idt_create_sysfs_files(pdev);
	अगर (ret != 0)
		जाओ err_मुक्त_pdev;

	/* Create debugfs files */
	idt_create_dbgfs_files(pdev);

	वापस 0;

err_मुक्त_pdev:
	idt_मुक्त_pdev(pdev);

	वापस ret;
पूर्ण

/*
 * idt_हटाओ() - IDT 89HPESx driver हटाओ() callback method
 */
अटल पूर्णांक idt_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा idt_89hpesx_dev *pdev = i2c_get_clientdata(client);

	/* Remove debugfs files first */
	idt_हटाओ_dbgfs_files(pdev);

	/* Remove sysfs files */
	idt_हटाओ_sysfs_files(pdev);

	/* Discard driver data काष्ठाure */
	idt_मुक्त_pdev(pdev);

	वापस 0;
पूर्ण

/*
 * ee_ids - array of supported EEPROMs
 */
अटल स्थिर काष्ठा i2c_device_id ee_ids[] = अणु
	अणु "24c32",  4096पूर्ण,
	अणु "24c64",  8192पूर्ण,
	अणु "24c128", 16384पूर्ण,
	अणु "24c256", 32768पूर्ण,
	अणु "24c512", 65536पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ee_ids);

/*
 * idt_ids - supported IDT 89HPESx devices
 */
अटल स्थिर काष्ठा i2c_device_id idt_ids[] = अणु
	अणु "89hpes8nt2", 0 पूर्ण,
	अणु "89hpes12nt3", 0 पूर्ण,

	अणु "89hpes24nt6ag2", 0 पूर्ण,
	अणु "89hpes32nt8ag2", 0 पूर्ण,
	अणु "89hpes32nt8bg2", 0 पूर्ण,
	अणु "89hpes12nt12g2", 0 पूर्ण,
	अणु "89hpes16nt16g2", 0 पूर्ण,
	अणु "89hpes24nt24g2", 0 पूर्ण,
	अणु "89hpes32nt24ag2", 0 पूर्ण,
	अणु "89hpes32nt24bg2", 0 पूर्ण,

	अणु "89hpes12n3", 0 पूर्ण,
	अणु "89hpes12n3a", 0 पूर्ण,
	अणु "89hpes24n3", 0 पूर्ण,
	अणु "89hpes24n3a", 0 पूर्ण,

	अणु "89hpes32h8", 0 पूर्ण,
	अणु "89hpes32h8g2", 0 पूर्ण,
	अणु "89hpes48h12", 0 पूर्ण,
	अणु "89hpes48h12g2", 0 पूर्ण,
	अणु "89hpes48h12ag2", 0 पूर्ण,
	अणु "89hpes16h16", 0 पूर्ण,
	अणु "89hpes22h16", 0 पूर्ण,
	अणु "89hpes22h16g2", 0 पूर्ण,
	अणु "89hpes34h16", 0 पूर्ण,
	अणु "89hpes34h16g2", 0 पूर्ण,
	अणु "89hpes64h16", 0 पूर्ण,
	अणु "89hpes64h16g2", 0 पूर्ण,
	अणु "89hpes64h16ag2", 0 पूर्ण,

	/* अणु "89hpes3t3", 0 पूर्ण, // No SMBus-slave अगरace */
	अणु "89hpes12t3g2", 0 पूर्ण,
	अणु "89hpes24t3g2", 0 पूर्ण,
	/* अणु "89hpes4t4", 0 पूर्ण, // No SMBus-slave अगरace */
	अणु "89hpes16t4", 0 पूर्ण,
	अणु "89hpes4t4g2", 0 पूर्ण,
	अणु "89hpes10t4g2", 0 पूर्ण,
	अणु "89hpes16t4g2", 0 पूर्ण,
	अणु "89hpes16t4ag2", 0 पूर्ण,
	अणु "89hpes5t5", 0 पूर्ण,
	अणु "89hpes6t5", 0 पूर्ण,
	अणु "89hpes8t5", 0 पूर्ण,
	अणु "89hpes8t5a", 0 पूर्ण,
	अणु "89hpes24t6", 0 पूर्ण,
	अणु "89hpes6t6g2", 0 पूर्ण,
	अणु "89hpes24t6g2", 0 पूर्ण,
	अणु "89hpes16t7", 0 पूर्ण,
	अणु "89hpes32t8", 0 पूर्ण,
	अणु "89hpes32t8g2", 0 पूर्ण,
	अणु "89hpes48t12", 0 पूर्ण,
	अणु "89hpes48t12g2", 0 पूर्ण,
	अणु /* END OF LIST */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, idt_ids);

अटल स्थिर काष्ठा of_device_id idt_of_match[] = अणु
	अणु .compatible = "idt,89hpes8nt2", पूर्ण,
	अणु .compatible = "idt,89hpes12nt3", पूर्ण,

	अणु .compatible = "idt,89hpes24nt6ag2", पूर्ण,
	अणु .compatible = "idt,89hpes32nt8ag2", पूर्ण,
	अणु .compatible = "idt,89hpes32nt8bg2", पूर्ण,
	अणु .compatible = "idt,89hpes12nt12g2", पूर्ण,
	अणु .compatible = "idt,89hpes16nt16g2", पूर्ण,
	अणु .compatible = "idt,89hpes24nt24g2", पूर्ण,
	अणु .compatible = "idt,89hpes32nt24ag2", पूर्ण,
	अणु .compatible = "idt,89hpes32nt24bg2", पूर्ण,

	अणु .compatible = "idt,89hpes12n3", पूर्ण,
	अणु .compatible = "idt,89hpes12n3a", पूर्ण,
	अणु .compatible = "idt,89hpes24n3", पूर्ण,
	अणु .compatible = "idt,89hpes24n3a", पूर्ण,

	अणु .compatible = "idt,89hpes32h8", पूर्ण,
	अणु .compatible = "idt,89hpes32h8g2", पूर्ण,
	अणु .compatible = "idt,89hpes48h12", पूर्ण,
	अणु .compatible = "idt,89hpes48h12g2", पूर्ण,
	अणु .compatible = "idt,89hpes48h12ag2", पूर्ण,
	अणु .compatible = "idt,89hpes16h16", पूर्ण,
	अणु .compatible = "idt,89hpes22h16", पूर्ण,
	अणु .compatible = "idt,89hpes22h16g2", पूर्ण,
	अणु .compatible = "idt,89hpes34h16", पूर्ण,
	अणु .compatible = "idt,89hpes34h16g2", पूर्ण,
	अणु .compatible = "idt,89hpes64h16", पूर्ण,
	अणु .compatible = "idt,89hpes64h16g2", पूर्ण,
	अणु .compatible = "idt,89hpes64h16ag2", पूर्ण,

	अणु .compatible = "idt,89hpes12t3g2", पूर्ण,
	अणु .compatible = "idt,89hpes24t3g2", पूर्ण,

	अणु .compatible = "idt,89hpes16t4", पूर्ण,
	अणु .compatible = "idt,89hpes4t4g2", पूर्ण,
	अणु .compatible = "idt,89hpes10t4g2", पूर्ण,
	अणु .compatible = "idt,89hpes16t4g2", पूर्ण,
	अणु .compatible = "idt,89hpes16t4ag2", पूर्ण,
	अणु .compatible = "idt,89hpes5t5", पूर्ण,
	अणु .compatible = "idt,89hpes6t5", पूर्ण,
	अणु .compatible = "idt,89hpes8t5", पूर्ण,
	अणु .compatible = "idt,89hpes8t5a", पूर्ण,
	अणु .compatible = "idt,89hpes24t6", पूर्ण,
	अणु .compatible = "idt,89hpes6t6g2", पूर्ण,
	अणु .compatible = "idt,89hpes24t6g2", पूर्ण,
	अणु .compatible = "idt,89hpes16t7", पूर्ण,
	अणु .compatible = "idt,89hpes32t8", पूर्ण,
	अणु .compatible = "idt,89hpes32t8g2", पूर्ण,
	अणु .compatible = "idt,89hpes48t12", पूर्ण,
	अणु .compatible = "idt,89hpes48t12g2", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, idt_of_match);

/*
 * idt_driver - IDT 89HPESx driver काष्ठाure
 */
अटल काष्ठा i2c_driver idt_driver = अणु
	.driver = अणु
		.name = IDT_NAME,
		.of_match_table = idt_of_match,
	पूर्ण,
	.probe = idt_probe,
	.हटाओ = idt_हटाओ,
	.id_table = idt_ids,
पूर्ण;

/*
 * idt_init() - IDT 89HPESx driver init() callback method
 */
अटल पूर्णांक __init idt_init(व्योम)
अणु
	/* Create Debugfs directory first */
	अगर (debugfs_initialized())
		csr_dbgdir = debugfs_create_dir("idt_csr", शून्य);

	/* Add new i2c-device driver */
	वापस i2c_add_driver(&idt_driver);
पूर्ण
module_init(idt_init);

/*
 * idt_निकास() - IDT 89HPESx driver निकास() callback method
 */
अटल व्योम __निकास idt_निकास(व्योम)
अणु
	/* Discard debugfs directory and all files अगर any */
	debugfs_हटाओ_recursive(csr_dbgdir);

	/* Unरेजिस्टर i2c-device driver */
	i2c_del_driver(&idt_driver);
पूर्ण
module_निकास(idt_निकास);
