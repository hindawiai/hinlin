<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2000 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#समावेश <linux/init.h>
#समावेश <linux/memblock.h>
#समावेश <linux/initrd.h>
#समावेश <यंत्र/types.h>
#समावेश <init.h>
#समावेश <os.h>

/* Changed by uml_initrd_setup, which is a setup */
अटल अक्षर *initrd __initdata = शून्य;
अटल पूर्णांक load_initrd(अक्षर *filename, व्योम *buf, पूर्णांक size);

पूर्णांक __init पढ़ो_initrd(व्योम)
अणु
	व्योम *area;
	दीर्घ दीर्घ size;
	पूर्णांक err;

	अगर (initrd == शून्य)
		वापस 0;

	err = os_file_size(initrd, &size);
	अगर (err)
		वापस 0;

	/*
	 * This is necessary because alloc_booपंचांगem craps out अगर you
	 * ask क्रम no memory.
	 */
	अगर (size == 0) अणु
		prपूर्णांकk(KERN_ERR "\"%s\" is a zero-size initrd\n", initrd);
		वापस 0;
	पूर्ण

	area = memblock_alloc(size, SMP_CACHE_BYTES);
	अगर (!area)
		panic("%s: Failed to allocate %llu bytes\n", __func__, size);

	अगर (load_initrd(initrd, area, size) == -1)
		वापस 0;

	initrd_start = (अचिन्हित दीर्घ) area;
	initrd_end = initrd_start + size;
	वापस 0;
पूर्ण

अटल पूर्णांक __init uml_initrd_setup(अक्षर *line, पूर्णांक *add)
अणु
	initrd = line;
	वापस 0;
पूर्ण

__uml_setup("initrd=", uml_initrd_setup,
"initrd=<initrd image>\n"
"    This is used to boot UML from an initrd image.  The argument is the\n"
"    name of the file containing the image.\n\n"
);

अटल पूर्णांक load_initrd(अक्षर *filename, व्योम *buf, पूर्णांक size)
अणु
	पूर्णांक fd, n;

	fd = os_खोलो_file(filename, of_पढ़ो(OPENFLAGS()), 0);
	अगर (fd < 0) अणु
		prपूर्णांकk(KERN_ERR "Opening '%s' failed - err = %d\n", filename,
		       -fd);
		वापस -1;
	पूर्ण
	n = os_पढ़ो_file(fd, buf, size);
	अगर (n != size) अणु
		prपूर्णांकk(KERN_ERR "Read of %d bytes from '%s' failed, "
		       "err = %d\n", size,
		       filename, -n);
		वापस -1;
	पूर्ण

	os_बंद_file(fd);
	वापस 0;
पूर्ण
