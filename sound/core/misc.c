<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Misc and compatibility things
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/समय.स>
#समावेश <linux/slab.h>
#समावेश <linux/ioport.h>
#समावेश <sound/core.h>

#अगर_घोषित CONFIG_SND_DEBUG

#अगर_घोषित CONFIG_SND_DEBUG_VERBOSE
#घोषणा DEFAULT_DEBUG_LEVEL	2
#अन्यथा
#घोषणा DEFAULT_DEBUG_LEVEL	1
#पूर्ण_अगर

अटल पूर्णांक debug = DEFAULT_DEBUG_LEVEL;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Debug level (0 = disable)");

#पूर्ण_अगर /* CONFIG_SND_DEBUG */

व्योम release_and_मुक्त_resource(काष्ठा resource *res)
अणु
	अगर (res) अणु
		release_resource(res);
		kमुक्त(res);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(release_and_मुक्त_resource);

#अगर_घोषित CONFIG_SND_VERBOSE_PRINTK
/* strip the leading path अगर the given path is असलolute */
अटल स्थिर अक्षर *sanity_file_name(स्थिर अक्षर *path)
अणु
	अगर (*path == '/')
		वापस म_खोजप(path, '/') + 1;
	अन्यथा
		वापस path;
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_SND_DEBUG) || defined(CONFIG_SND_VERBOSE_PRINTK)
व्योम __snd_prपूर्णांकk(अचिन्हित पूर्णांक level, स्थिर अक्षर *path, पूर्णांक line,
		  स्थिर अक्षर *क्रमmat, ...)
अणु
	बहु_सूची args;
#अगर_घोषित CONFIG_SND_VERBOSE_PRINTK
	पूर्णांक kern_level;
	काष्ठा va_क्रमmat vaf;
	अक्षर verbose_fmt[] = KERN_DEFAULT "ALSA %s:%d %pV";
	bool level_found = false;
#पूर्ण_अगर

#अगर_घोषित CONFIG_SND_DEBUG
	अगर (debug < level)
		वापस;
#पूर्ण_अगर

	बहु_शुरू(args, क्रमmat);
#अगर_घोषित CONFIG_SND_VERBOSE_PRINTK
	vaf.fmt = क्रमmat;
	vaf.va = &args;

	जबतक ((kern_level = prपूर्णांकk_get_level(vaf.fmt)) != 0) अणु
		स्थिर अक्षर *end_of_header = prपूर्णांकk_skip_level(vaf.fmt);

		/* Ignore KERN_CONT. We prपूर्णांक filename:line क्रम each piece. */
		अगर (kern_level >= '0' && kern_level <= '7') अणु
			स_नकल(verbose_fmt, vaf.fmt, end_of_header - vaf.fmt);
			level_found = true;
		पूर्ण

		vaf.fmt = end_of_header;
	पूर्ण

	अगर (!level_found && level)
		स_नकल(verbose_fmt, KERN_DEBUG, माप(KERN_DEBUG) - 1);

	prपूर्णांकk(verbose_fmt, sanity_file_name(path), line, &vaf);
#अन्यथा
	vprपूर्णांकk(क्रमmat, args);
#पूर्ण_अगर
	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL_GPL(__snd_prपूर्णांकk);
#पूर्ण_अगर

#अगर_घोषित CONFIG_PCI
#समावेश <linux/pci.h>
/**
 * snd_pci_quirk_lookup_id - look up a PCI SSID quirk list
 * @venकरोr: PCI SSV id
 * @device: PCI SSD id
 * @list: quirk list, terminated by a null entry
 *
 * Look through the given quirk list and finds a matching entry
 * with the same PCI SSID.  When subdevice is 0, all subdevice
 * values may match.
 *
 * Returns the matched entry poपूर्णांकer, or शून्य अगर nothing matched.
 */
स्थिर काष्ठा snd_pci_quirk *
snd_pci_quirk_lookup_id(u16 venकरोr, u16 device,
			स्थिर काष्ठा snd_pci_quirk *list)
अणु
	स्थिर काष्ठा snd_pci_quirk *q;

	क्रम (q = list; q->subvenकरोr; q++) अणु
		अगर (q->subvenकरोr != venकरोr)
			जारी;
		अगर (!q->subdevice ||
		    (device & q->subdevice_mask) == q->subdevice)
			वापस q;
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(snd_pci_quirk_lookup_id);

/**
 * snd_pci_quirk_lookup - look up a PCI SSID quirk list
 * @pci: pci_dev handle
 * @list: quirk list, terminated by a null entry
 *
 * Look through the given quirk list and finds a matching entry
 * with the same PCI SSID.  When subdevice is 0, all subdevice
 * values may match.
 *
 * Returns the matched entry poपूर्णांकer, or शून्य अगर nothing matched.
 */
स्थिर काष्ठा snd_pci_quirk *
snd_pci_quirk_lookup(काष्ठा pci_dev *pci, स्थिर काष्ठा snd_pci_quirk *list)
अणु
	अगर (!pci)
		वापस शून्य;
	वापस snd_pci_quirk_lookup_id(pci->subप्रणाली_venकरोr,
				       pci->subप्रणाली_device,
				       list);
पूर्ण
EXPORT_SYMBOL(snd_pci_quirk_lookup);
#पूर्ण_अगर
