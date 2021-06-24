<शैली गुरु>
/*
 * Mapping of a custom board with both AMD CFI and JEDEC flash in partitions.
 * Config with both CFI and JEDEC device support.
 *
 * Basically physmap.c with the addition of partitions and
 * an array of mapping info to accommodate more than one flash type per board.
 *
 * Copyright 2005-2007 PMC-Sierra, Inc.
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

#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/map.h>
#समावेश <linux/mtd/partitions.h>

#समावेश <यंत्र/पन.स>

#समावेश <msp_prom.h>
#समावेश <msp_regs.h>


अटल काष्ठा mtd_info **msp_flash;
अटल काष्ठा mtd_partition **msp_parts;
अटल काष्ठा map_info *msp_maps;
अटल पूर्णांक fcnt;

#घोषणा DEBUG_MARKER prपूर्णांकk(KERN_NOTICE "%s[%d]\n", __func__, __LINE__)

अटल पूर्णांक __init init_msp_flash(व्योम)
अणु
	पूर्णांक i, j, ret = -ENOMEM;
	पूर्णांक offset, coff;
	अक्षर *env;
	पूर्णांक pcnt;
	अक्षर flash_name[] = "flash0";
	अक्षर part_name[] = "flash0_0";
	अचिन्हित addr, size;

	/* If ELB is disabled by "ful-mux" mode, we can't get at flash */
	अगर ((*DEV_ID_REG & DEV_ID_SINGLE_PC) &&
	    (*ELB_1PC_EN_REG & SINGLE_PCCARD)) अणु
		prपूर्णांकk(KERN_NOTICE "Single PC Card mode: no flash access\n");
		वापस -ENXIO;
	पूर्ण

	/* examine the prom environment क्रम flash devices */
	क्रम (fcnt = 0; (env = prom_दो_पर्या(flash_name)); fcnt++)
		flash_name[5] = '0' + fcnt + 1;

	अगर (fcnt < 1)
		वापस -ENXIO;

	prपूर्णांकk(KERN_NOTICE "Found %d PMC flash devices\n", fcnt);

	msp_flash = kसुस्मृति(fcnt, माप(*msp_flash), GFP_KERNEL);
	अगर (!msp_flash)
		वापस -ENOMEM;

	msp_parts = kसुस्मृति(fcnt, माप(*msp_parts), GFP_KERNEL);
	अगर (!msp_parts)
		जाओ मुक्त_msp_flash;

	msp_maps = kसुस्मृति(fcnt, माप(*msp_maps), GFP_KERNEL);
	अगर (!msp_maps)
		जाओ मुक्त_msp_parts;

	/* loop over the flash devices, initializing each */
	क्रम (i = 0; i < fcnt; i++) अणु
		/* examine the prom environment क्रम flash partititions */
		part_name[5] = '0' + i;
		part_name[7] = '0';
		क्रम (pcnt = 0; (env = prom_दो_पर्या(part_name)); pcnt++)
			part_name[7] = '0' + pcnt + 1;

		अगर (pcnt == 0) अणु
			prपूर्णांकk(KERN_NOTICE "Skipping flash device %d "
				"(no partitions defined)\n", i);
			जारी;
		पूर्ण

		msp_parts[i] = kसुस्मृति(pcnt, माप(काष्ठा mtd_partition),
				       GFP_KERNEL);
		अगर (!msp_parts[i])
			जाओ cleanup_loop;

		/* now initialize the devices proper */
		flash_name[5] = '0' + i;
		env = prom_दो_पर्या(flash_name);

		अगर (माला_पूछो(env, "%x:%x", &addr, &size) < 2) अणु
			ret = -ENXIO;
			kमुक्त(msp_parts[i]);
			जाओ cleanup_loop;
		पूर्ण
		addr = CPHYSADDR(addr);

		prपूर्णांकk(KERN_NOTICE
			"MSP flash device \"%s\": 0x%08x at 0x%08x\n",
			flash_name, size, addr);
		/* This must matchs the actual size of the flash chip */
		msp_maps[i].size = size;
		msp_maps[i].phys = addr;

		/*
		 * Platक्रमms have a specअगरic limit of the size of memory
		 * which may be mapped क्रम flash:
		 */
		अगर (size > CONFIG_MSP_FLASH_MAP_LIMIT)
			size = CONFIG_MSP_FLASH_MAP_LIMIT;

		msp_maps[i].virt = ioremap(addr, size);
		अगर (msp_maps[i].virt == शून्य) अणु
			ret = -ENXIO;
			kमुक्त(msp_parts[i]);
			जाओ cleanup_loop;
		पूर्ण

		msp_maps[i].bankwidth = 1;
		msp_maps[i].name = kstrndup(flash_name, 7, GFP_KERNEL);
		अगर (!msp_maps[i].name) अणु
			iounmap(msp_maps[i].virt);
			kमुक्त(msp_parts[i]);
			जाओ cleanup_loop;
		पूर्ण

		क्रम (j = 0; j < pcnt; j++) अणु
			part_name[5] = '0' + i;
			part_name[7] = '0' + j;

			env = prom_दो_पर्या(part_name);

			अगर (माला_पूछो(env, "%x:%x:%n", &offset, &size,
						&coff) < 2) अणु
				ret = -ENXIO;
				kमुक्त(msp_maps[i].name);
				iounmap(msp_maps[i].virt);
				kमुक्त(msp_parts[i]);
				जाओ cleanup_loop;
			पूर्ण

			msp_parts[i][j].size = size;
			msp_parts[i][j].offset = offset;
			msp_parts[i][j].name = env + coff;
		पूर्ण

		/* now probe and add the device */
		simple_map_init(&msp_maps[i]);
		msp_flash[i] = करो_map_probe("cfi_probe", &msp_maps[i]);
		अगर (msp_flash[i]) अणु
			msp_flash[i]->owner = THIS_MODULE;
			mtd_device_रेजिस्टर(msp_flash[i], msp_parts[i], pcnt);
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_ERR "map probe failed for flash\n");
			ret = -ENXIO;
			kमुक्त(msp_maps[i].name);
			iounmap(msp_maps[i].virt);
			kमुक्त(msp_parts[i]);
			जाओ cleanup_loop;
		पूर्ण
	पूर्ण

	वापस 0;

cleanup_loop:
	जबतक (i--) अणु
		mtd_device_unरेजिस्टर(msp_flash[i]);
		map_destroy(msp_flash[i]);
		kमुक्त(msp_maps[i].name);
		iounmap(msp_maps[i].virt);
		kमुक्त(msp_parts[i]);
	पूर्ण
	kमुक्त(msp_maps);
मुक्त_msp_parts:
	kमुक्त(msp_parts);
मुक्त_msp_flash:
	kमुक्त(msp_flash);
	वापस ret;
पूर्ण

अटल व्योम __निकास cleanup_msp_flash(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < fcnt; i++) अणु
		mtd_device_unरेजिस्टर(msp_flash[i]);
		map_destroy(msp_flash[i]);
		iounmap((व्योम *)msp_maps[i].virt);

		/* मुक्त the memory */
		kमुक्त(msp_maps[i].name);
		kमुक्त(msp_parts[i]);
	पूर्ण

	kमुक्त(msp_flash);
	kमुक्त(msp_parts);
	kमुक्त(msp_maps);
पूर्ण

MODULE_AUTHOR("PMC-Sierra, Inc");
MODULE_DESCRIPTION("MTD map driver for PMC-Sierra MSP boards");
MODULE_LICENSE("GPL");

module_init(init_msp_flash);
module_निकास(cleanup_msp_flash);
