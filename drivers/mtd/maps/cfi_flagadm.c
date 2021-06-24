<शैली गुरु>
/*
 *  Copyright तऊ 2001 Flaga hf. Medical Devices, Kथँri Davथऐथओsson <kd@flaga.is>
 *
 *  This program is मुक्त software; you can redistribute  it and/or modअगरy it
 *  under  the terms of  the GNU General  Public License as published by the
 *  Free Software Foundation;  either version 2 of the  License, or (at your
 *  option) any later version.
 *
 *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS'' AND   ANY  EXPRESS OR IMPLIED
 *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
 *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   सूचीECT, INसूचीECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF
 *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  You should have received a copy of the  GNU General Public License aदीर्घ
 *  with this program; अगर not, ग_लिखो  to the Free Software Foundation, Inc.,
 *  675 Mass Ave, Cambridge, MA 02139, USA.
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/map.h>
#समावेश <linux/mtd/partitions.h>


/* We split the flash chip up पूर्णांकo four parts.
 * 1: bootloader first 128k			(0x00000000 - 0x0001FFFF) size 0x020000
 * 2: kernel 640k					(0x00020000 - 0x000BFFFF) size 0x0A0000
 * 3: compressed 1536k root ramdisk	(0x000C0000 - 0x0023FFFF) size 0x180000
 * 4: ग_लिखोable diskpartition (jffs)(0x00240000 - 0x003FFFFF) size 0x1C0000
 */

#घोषणा FLASH_PHYS_ADDR 0x40000000
#घोषणा FLASH_SIZE 0x400000

#घोषणा FLASH_PARTITION0_ADDR 0x00000000
#घोषणा FLASH_PARTITION0_SIZE 0x00020000

#घोषणा FLASH_PARTITION1_ADDR 0x00020000
#घोषणा FLASH_PARTITION1_SIZE 0x000A0000

#घोषणा FLASH_PARTITION2_ADDR 0x000C0000
#घोषणा FLASH_PARTITION2_SIZE 0x00180000

#घोषणा FLASH_PARTITION3_ADDR 0x00240000
#घोषणा FLASH_PARTITION3_SIZE 0x001C0000


अटल काष्ठा map_info flagadm_map = अणु
		.name =		"FlagaDM flash device",
		.size =		FLASH_SIZE,
		.bankwidth =	2,
पूर्ण;

अटल स्थिर काष्ठा mtd_partition flagadm_parts[] = अणु
	अणु
		.name =		"Bootloader",
		.offset	=	FLASH_PARTITION0_ADDR,
		.size =		FLASH_PARTITION0_SIZE
	पूर्ण,
	अणु
		.name =		"Kernel image",
		.offset =	FLASH_PARTITION1_ADDR,
		.size =		FLASH_PARTITION1_SIZE
	पूर्ण,
	अणु
		.name =		"Initial ramdisk image",
		.offset =	FLASH_PARTITION2_ADDR,
		.size =		FLASH_PARTITION2_SIZE
	पूर्ण,
	अणु
		.name =		"Persistent storage",
		.offset =	FLASH_PARTITION3_ADDR,
		.size =		FLASH_PARTITION3_SIZE
	पूर्ण
पूर्ण;

#घोषणा PARTITION_COUNT ARRAY_SIZE(flagadm_parts)

अटल काष्ठा mtd_info *mymtd;

अटल पूर्णांक __init init_flagadm(व्योम)
अणु
	prपूर्णांकk(KERN_NOTICE "FlagaDM flash device: %x at %x\n",
			FLASH_SIZE, FLASH_PHYS_ADDR);

	flagadm_map.phys = FLASH_PHYS_ADDR;
	flagadm_map.virt = ioremap(FLASH_PHYS_ADDR,
					FLASH_SIZE);

	अगर (!flagadm_map.virt) अणु
		prपूर्णांकk("Failed to ioremap\n");
		वापस -EIO;
	पूर्ण

	simple_map_init(&flagadm_map);

	mymtd = करो_map_probe("cfi_probe", &flagadm_map);
	अगर (mymtd) अणु
		mymtd->owner = THIS_MODULE;
		mtd_device_रेजिस्टर(mymtd, flagadm_parts, PARTITION_COUNT);
		prपूर्णांकk(KERN_NOTICE "FlagaDM flash device initialized\n");
		वापस 0;
	पूर्ण

	iounmap((व्योम __iomem *)flagadm_map.virt);
	वापस -ENXIO;
पूर्ण

अटल व्योम __निकास cleanup_flagadm(व्योम)
अणु
	अगर (mymtd) अणु
		mtd_device_unरेजिस्टर(mymtd);
		map_destroy(mymtd);
	पूर्ण
	अगर (flagadm_map.virt) अणु
		iounmap((व्योम __iomem *)flagadm_map.virt);
		flagadm_map.virt = शून्य;
	पूर्ण
पूर्ण

module_init(init_flagadm);
module_निकास(cleanup_flagadm);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kथँri Davथऐथओsson <kd@flaga.is>");
MODULE_DESCRIPTION("MTD map driver for Flaga digital module");
