<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * tsunami_flash.c
 *
 * flash chip on alpha ds10...
 */
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/core_tsunami.h>
#समावेश <linux/init.h>
#समावेश <linux/mtd/map.h>
#समावेश <linux/mtd/mtd.h>

#घोषणा FLASH_ENABLE_PORT 0x00C00001
#घोषणा FLASH_ENABLE_BYTE 0x01
#घोषणा FLASH_DISABLE_BYTE 0x00

#घोषणा MAX_TIG_FLASH_SIZE (12*1024*1024)
अटल अंतरभूत map_word tsunami_flash_पढ़ो8(काष्ठा map_info *map, अचिन्हित दीर्घ offset)
अणु
	map_word val;
	val.x[0] = tsunami_tig_पढ़ोb(offset);
	वापस val;
पूर्ण

अटल व्योम tsunami_flash_ग_लिखो8(काष्ठा map_info *map, map_word value, अचिन्हित दीर्घ offset)
अणु
	tsunami_tig_ग_लिखोb(value.x[0], offset);
पूर्ण

अटल व्योम tsunami_flash_copy_from(
	काष्ठा map_info *map, व्योम *addr, अचिन्हित दीर्घ offset, sमाप_प्रकार len)
अणु
	अचिन्हित अक्षर *dest;
	dest = addr;
	जबतक(len && (offset < MAX_TIG_FLASH_SIZE)) अणु
		*dest = tsunami_tig_पढ़ोb(offset);
		offset++;
		dest++;
		len--;
	पूर्ण
पूर्ण

अटल व्योम tsunami_flash_copy_to(
	काष्ठा map_info *map, अचिन्हित दीर्घ offset,
	स्थिर व्योम *addr, sमाप_प्रकार len)
अणु
	स्थिर अचिन्हित अक्षर *src;
	src = addr;
	जबतक(len && (offset < MAX_TIG_FLASH_SIZE)) अणु
		tsunami_tig_ग_लिखोb(*src, offset);
		offset++;
		src++;
		len--;
	पूर्ण
पूर्ण

/*
 * Deliberately करोn't provide operations wider than 8 bits.  I don't
 * have then and it scares me to think how you could mess up अगर
 * you tried to use them.   Buswidth is correctly so I'm safe.
 */
अटल काष्ठा map_info tsunami_flash_map = अणु
	.name = "flash chip on the Tsunami TIG bus",
	.size = MAX_TIG_FLASH_SIZE,
	.phys = NO_XIP,
	.bankwidth = 1,
	.पढ़ो = tsunami_flash_पढ़ो8,
	.copy_from = tsunami_flash_copy_from,
	.ग_लिखो = tsunami_flash_ग_लिखो8,
	.copy_to = tsunami_flash_copy_to,
पूर्ण;

अटल काष्ठा mtd_info *tsunami_flash_mtd;

अटल व्योम __निकास  cleanup_tsunami_flash(व्योम)
अणु
	काष्ठा mtd_info *mtd;
	mtd = tsunami_flash_mtd;
	अगर (mtd) अणु
		mtd_device_unरेजिस्टर(mtd);
		map_destroy(mtd);
	पूर्ण
	tsunami_flash_mtd = 0;
पूर्ण

अटल स्थिर अक्षर * स्थिर rom_probe_types[] = अणु
	"cfi_probe", "jedec_probe", "map_rom", शून्य पूर्ण;

अटल पूर्णांक __init init_tsunami_flash(व्योम)
अणु
	स्थिर अक्षर * स्थिर *type;

	tsunami_tig_ग_लिखोb(FLASH_ENABLE_BYTE, FLASH_ENABLE_PORT);

	tsunami_flash_mtd = 0;
	type = rom_probe_types;
	क्रम(; !tsunami_flash_mtd && *type; type++) अणु
		tsunami_flash_mtd = करो_map_probe(*type, &tsunami_flash_map);
	पूर्ण
	अगर (tsunami_flash_mtd) अणु
		tsunami_flash_mtd->owner = THIS_MODULE;
		mtd_device_रेजिस्टर(tsunami_flash_mtd, शून्य, 0);
		वापस 0;
	पूर्ण
	वापस -ENXIO;
पूर्ण

module_init(init_tsunami_flash);
module_निकास(cleanup_tsunami_flash);
