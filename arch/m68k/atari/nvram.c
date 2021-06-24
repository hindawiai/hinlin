<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * CMOS/NV-RAM driver क्रम Atari. Adapted from drivers/अक्षर/nvram.c.
 * Copyright (C) 1997 Roman Hodek <Roman.Hodek@inक्रमmatik.uni-erlangen.de>
 * idea by and with help from Riअक्षरd Jelinek <rj@suse.de>
 * Portions copyright (c) 2001,2002 Sun Microप्रणालीs (thockin@sun.com)
 * Further contributions from Cesar Barros, Erik Gilling, Tim Hockin and
 * Wim Van Sebroeck.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/mc146818rtc.h>
#समावेश <linux/module.h>
#समावेश <linux/nvram.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/atarihw.h>
#समावेश <यंत्र/atariपूर्णांकs.h>

#घोषणा NVRAM_BYTES		50

/* It is worth noting that these functions all access bytes of general
 * purpose memory in the NVRAM - that is to say, they all add the
 * NVRAM_FIRST_BYTE offset. Pass them offsets पूर्णांकo NVRAM as अगर you did not
 * know about the RTC cruft.
 */

/* Note that *all* calls to CMOS_READ and CMOS_WRITE must be करोne with
 * rtc_lock held. Due to the index-port/data-port design of the RTC, we
 * करोn't want two dअगरferent things trying to get to it at once. (e.g. the
 * periodic 11 min sync from kernel/समय/ntp.c vs. this driver.)
 */

अटल अचिन्हित अक्षर __nvram_पढ़ो_byte(पूर्णांक i)
अणु
	वापस CMOS_READ(NVRAM_FIRST_BYTE + i);
पूर्ण

/* This races nicely with trying to पढ़ो with checksum checking */
अटल व्योम __nvram_ग_लिखो_byte(अचिन्हित अक्षर c, पूर्णांक i)
अणु
	CMOS_WRITE(c, NVRAM_FIRST_BYTE + i);
पूर्ण

/* On Ataris, the checksum is over all bytes except the checksum bytes
 * themselves; these are at the very end.
 */
#घोषणा ATARI_CKS_RANGE_START	0
#घोषणा ATARI_CKS_RANGE_END	47
#घोषणा ATARI_CKS_LOC		48

अटल पूर्णांक __nvram_check_checksum(व्योम)
अणु
	पूर्णांक i;
	अचिन्हित अक्षर sum = 0;

	क्रम (i = ATARI_CKS_RANGE_START; i <= ATARI_CKS_RANGE_END; ++i)
		sum += __nvram_पढ़ो_byte(i);
	वापस (__nvram_पढ़ो_byte(ATARI_CKS_LOC) == (~sum & 0xff)) &&
	       (__nvram_पढ़ो_byte(ATARI_CKS_LOC + 1) == (sum & 0xff));
पूर्ण

अटल व्योम __nvram_set_checksum(व्योम)
अणु
	पूर्णांक i;
	अचिन्हित अक्षर sum = 0;

	क्रम (i = ATARI_CKS_RANGE_START; i <= ATARI_CKS_RANGE_END; ++i)
		sum += __nvram_पढ़ो_byte(i);
	__nvram_ग_लिखो_byte(~sum, ATARI_CKS_LOC);
	__nvram_ग_लिखो_byte(sum, ATARI_CKS_LOC + 1);
पूर्ण

दीर्घ atari_nvram_set_checksum(व्योम)
अणु
	spin_lock_irq(&rtc_lock);
	__nvram_set_checksum();
	spin_unlock_irq(&rtc_lock);
	वापस 0;
पूर्ण

दीर्घ atari_nvram_initialize(व्योम)
अणु
	loff_t i;

	spin_lock_irq(&rtc_lock);
	क्रम (i = 0; i < NVRAM_BYTES; ++i)
		__nvram_ग_लिखो_byte(0, i);
	__nvram_set_checksum();
	spin_unlock_irq(&rtc_lock);
	वापस 0;
पूर्ण

sमाप_प्रकार atari_nvram_पढ़ो(अक्षर *buf, माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर *p = buf;
	loff_t i;

	spin_lock_irq(&rtc_lock);
	अगर (!__nvram_check_checksum()) अणु
		spin_unlock_irq(&rtc_lock);
		वापस -EIO;
	पूर्ण
	क्रम (i = *ppos; count > 0 && i < NVRAM_BYTES; --count, ++i, ++p)
		*p = __nvram_पढ़ो_byte(i);
	spin_unlock_irq(&rtc_lock);

	*ppos = i;
	वापस p - buf;
पूर्ण

sमाप_प्रकार atari_nvram_ग_लिखो(अक्षर *buf, माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर *p = buf;
	loff_t i;

	spin_lock_irq(&rtc_lock);
	अगर (!__nvram_check_checksum()) अणु
		spin_unlock_irq(&rtc_lock);
		वापस -EIO;
	पूर्ण
	क्रम (i = *ppos; count > 0 && i < NVRAM_BYTES; --count, ++i, ++p)
		__nvram_ग_लिखो_byte(*p, i);
	__nvram_set_checksum();
	spin_unlock_irq(&rtc_lock);

	*ppos = i;
	वापस p - buf;
पूर्ण

sमाप_प्रकार atari_nvram_get_size(व्योम)
अणु
	वापस NVRAM_BYTES;
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
अटल काष्ठा अणु
	अचिन्हित अक्षर val;
	स्थिर अक्षर *name;
पूर्ण boot_prefs[] = अणु
	अणु 0x80, "TOS" पूर्ण,
	अणु 0x40, "ASV" पूर्ण,
	अणु 0x20, "NetBSD (?)" पूर्ण,
	अणु 0x10, "Linux" पूर्ण,
	अणु 0x00, "unspecified" पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर languages[] = अणु
	"English (US)",
	"German",
	"French",
	"English (UK)",
	"Spanish",
	"Italian",
	"6 (undefined)",
	"Swiss (French)",
	"Swiss (German)",
पूर्ण;

अटल स्थिर अक्षर * स्थिर dateक्रमmat[] = अणु
	"MM%cDD%cYY",
	"DD%cMM%cYY",
	"YY%cMM%cDD",
	"YY%cDD%cMM",
	"4 (undefined)",
	"5 (undefined)",
	"6 (undefined)",
	"7 (undefined)",
पूर्ण;

अटल स्थिर अक्षर * स्थिर colors[] = अणु
	"2", "4", "16", "256", "65536", "??", "??", "??"
पूर्ण;

अटल व्योम atari_nvram_proc_पढ़ो(अचिन्हित अक्षर *nvram, काष्ठा seq_file *seq,
				  व्योम *offset)
अणु
	पूर्णांक checksum;
	पूर्णांक i;
	अचिन्हित पूर्णांक vmode;

	spin_lock_irq(&rtc_lock);
	checksum = __nvram_check_checksum();
	spin_unlock_irq(&rtc_lock);

	seq_म_लिखो(seq, "Checksum status  : %svalid\n", checksum ? "" : "not ");

	seq_माला_दो(seq, "Boot preference  : ");
	क्रम (i = ARRAY_SIZE(boot_prefs) - 1; i >= 0; --i)
		अगर (nvram[1] == boot_prefs[i].val) अणु
			seq_म_लिखो(seq, "%s\n", boot_prefs[i].name);
			अवरोध;
		पूर्ण
	अगर (i < 0)
		seq_म_लिखो(seq, "0x%02x (undefined)\n", nvram[1]);

	seq_म_लिखो(seq, "SCSI arbitration : %s\n",
		   (nvram[16] & 0x80) ? "on" : "off");
	seq_माला_दो(seq, "SCSI host ID     : ");
	अगर (nvram[16] & 0x80)
		seq_म_लिखो(seq, "%d\n", nvram[16] & 7);
	अन्यथा
		seq_माला_दो(seq, "n/a\n");

	अगर (!MACH_IS_FALCON)
		वापस;

	seq_माला_दो(seq, "OS language      : ");
	अगर (nvram[6] < ARRAY_SIZE(languages))
		seq_म_लिखो(seq, "%s\n", languages[nvram[6]]);
	अन्यथा
		seq_म_लिखो(seq, "%u (undefined)\n", nvram[6]);
	seq_माला_दो(seq, "Keyboard language: ");
	अगर (nvram[7] < ARRAY_SIZE(languages))
		seq_म_लिखो(seq, "%s\n", languages[nvram[7]]);
	अन्यथा
		seq_म_लिखो(seq, "%u (undefined)\n", nvram[7]);
	seq_माला_दो(seq, "Date format      : ");
	seq_म_लिखो(seq, dateक्रमmat[nvram[8] & 7],
		   nvram[9] ? nvram[9] : '/', nvram[9] ? nvram[9] : '/');
	seq_म_लिखो(seq, ", %dh clock\n", nvram[8] & 16 ? 24 : 12);
	seq_माला_दो(seq, "Boot delay       : ");
	अगर (nvram[10] == 0)
		seq_माला_दो(seq, "default\n");
	अन्यथा
		seq_म_लिखो(seq, "%ds%s\n", nvram[10],
			   nvram[10] < 8 ? ", no memory test" : "");

	vmode = (nvram[14] << 8) | nvram[15];
	seq_म_लिखो(seq,
		   "Video mode       : %s colors, %d columns, %s %s monitor\n",
		   colors[vmode & 7], vmode & 8 ? 80 : 40,
		   vmode & 16 ? "VGA" : "TV", vmode & 32 ? "PAL" : "NTSC");
	seq_म_लिखो(seq,
		   "                   %soverscan, compat. mode %s%s\n",
		   vmode & 64 ? "" : "no ", vmode & 128 ? "on" : "off",
		   vmode & 256 ?
		   (vmode & 16 ? ", line doubling" : ", half screen") : "");
पूर्ण

अटल पूर्णांक nvram_proc_पढ़ो(काष्ठा seq_file *seq, व्योम *offset)
अणु
	अचिन्हित अक्षर contents[NVRAM_BYTES];
	पूर्णांक i;

	spin_lock_irq(&rtc_lock);
	क्रम (i = 0; i < NVRAM_BYTES; ++i)
		contents[i] = __nvram_पढ़ो_byte(i);
	spin_unlock_irq(&rtc_lock);

	atari_nvram_proc_पढ़ो(contents, seq, offset);

	वापस 0;
पूर्ण

अटल पूर्णांक __init atari_nvram_init(व्योम)
अणु
	अगर (!(MACH_IS_ATARI && ATARIHW_PRESENT(TT_CLK)))
		वापस -ENODEV;

	अगर (!proc_create_single("driver/nvram", 0, शून्य, nvram_proc_पढ़ो)) अणु
		pr_err("nvram: can't create /proc/driver/nvram\n");
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण
device_initcall(atari_nvram_init);
#पूर्ण_अगर /* CONFIG_PROC_FS */
