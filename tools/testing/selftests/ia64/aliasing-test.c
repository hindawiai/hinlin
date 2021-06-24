<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Exercise /dev/mem mmap हालs that have been troublesome in the past
 *
 * (c) Copyright 2007 Hewlett-Packard Development Company, L.P.
 *	Bjorn Helgaas <bjorn.helgaas@hp.com>
 */

#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <sys/types.h>
#समावेश <dirent.h>
#समावेश <fcntl.h>
#समावेश <fnmatch.h>
#समावेश <माला.स>
#समावेश <sys/ioctl.h>
#समावेश <sys/mman.h>
#समावेश <sys/स्थिति.स>
#समावेश <unistd.h>
#समावेश <linux/pci.h>

पूर्णांक sum;

अटल पूर्णांक map_mem(अक्षर *path, off_t offset, माप_प्रकार length, पूर्णांक touch)
अणु
	पूर्णांक fd, rc;
	व्योम *addr;
	पूर्णांक *c;

	fd = खोलो(path, O_RDWR);
	अगर (fd == -1) अणु
		लिखो_त्रुटि(path);
		वापस -1;
	पूर्ण

	अगर (fnmatch("/proc/bus/pci/*", path, 0) == 0) अणु
		rc = ioctl(fd, PCIIOC_MMAP_IS_MEM);
		अगर (rc == -1)
			लिखो_त्रुटि("PCIIOC_MMAP_IS_MEM ioctl");
	पूर्ण

	addr = mmap(शून्य, length, PROT_READ|PROT_WRITE, MAP_SHARED, fd, offset);
	अगर (addr == MAP_FAILED)
		वापस 1;

	अगर (touch) अणु
		c = (पूर्णांक *) addr;
		जबतक (c < (पूर्णांक *) (addr + length))
			sum += *c++;
	पूर्ण

	rc = munmap(addr, length);
	अगर (rc == -1) अणु
		लिखो_त्रुटि("munmap");
		वापस -1;
	पूर्ण

	बंद(fd);
	वापस 0;
पूर्ण

अटल पूर्णांक scan_tree(अक्षर *path, अक्षर *file, off_t offset, माप_प्रकार length, पूर्णांक touch)
अणु
	काष्ठा dirent **namelist;
	अक्षर *name, *path2;
	पूर्णांक i, n, r, rc = 0, result = 0;
	काष्ठा stat buf;

	n = scandir(path, &namelist, 0, alphasort);
	अगर (n < 0) अणु
		लिखो_त्रुटि("scandir");
		वापस -1;
	पूर्ण

	क्रम (i = 0; i < n; i++) अणु
		name = namelist[i]->d_name;

		अगर (fnmatch(".", name, 0) == 0)
			जाओ skip;
		अगर (fnmatch("..", name, 0) == 0)
			जाओ skip;

		path2 = दो_स्मृति(म_माप(path) + म_माप(name) + 3);
		म_नकल(path2, path);
		म_जोड़ो(path2, "/");
		म_जोड़ो(path2, name);

		अगर (fnmatch(file, name, 0) == 0) अणु
			rc = map_mem(path2, offset, length, touch);
			अगर (rc == 0)
				ख_लिखो(मानक_त्रुटि, "PASS: %s 0x%lx-0x%lx is %s\n", path2, offset, offset + length, touch ? "readable" : "mappable");
			अन्यथा अगर (rc > 0)
				ख_लिखो(मानक_त्रुटि, "PASS: %s 0x%lx-0x%lx not mappable\n", path2, offset, offset + length);
			अन्यथा अणु
				ख_लिखो(मानक_त्रुटि, "FAIL: %s 0x%lx-0x%lx not accessible\n", path2, offset, offset + length);
				वापस rc;
			पूर्ण
		पूर्ण अन्यथा अणु
			r = lstat(path2, &buf);
			अगर (r == 0 && S_ISसूची(buf.st_mode)) अणु
				rc = scan_tree(path2, file, offset, length, touch);
				अगर (rc < 0)
					वापस rc;
			पूर्ण
		पूर्ण

		result |= rc;
		मुक्त(path2);

skip:
		मुक्त(namelist[i]);
	पूर्ण
	मुक्त(namelist);
	वापस result;
पूर्ण

अक्षर buf[1024];

अटल पूर्णांक पढ़ो_rom(अक्षर *path)
अणु
	पूर्णांक fd, rc;
	माप_प्रकार size = 0;

	fd = खोलो(path, O_RDWR);
	अगर (fd == -1) अणु
		लिखो_त्रुटि(path);
		वापस -1;
	पूर्ण

	rc = ग_लिखो(fd, "1", 2);
	अगर (rc <= 0) अणु
		बंद(fd);
		लिखो_त्रुटि("write");
		वापस -1;
	पूर्ण

	करो अणु
		rc = पढ़ो(fd, buf, माप(buf));
		अगर (rc > 0)
			size += rc;
	पूर्ण जबतक (rc > 0);

	बंद(fd);
	वापस size;
पूर्ण

अटल पूर्णांक scan_rom(अक्षर *path, अक्षर *file)
अणु
	काष्ठा dirent **namelist;
	अक्षर *name, *path2;
	पूर्णांक i, n, r, rc = 0, result = 0;
	काष्ठा stat buf;

	n = scandir(path, &namelist, 0, alphasort);
	अगर (n < 0) अणु
		लिखो_त्रुटि("scandir");
		वापस -1;
	पूर्ण

	क्रम (i = 0; i < n; i++) अणु
		name = namelist[i]->d_name;

		अगर (fnmatch(".", name, 0) == 0)
			जाओ skip;
		अगर (fnmatch("..", name, 0) == 0)
			जाओ skip;

		path2 = दो_स्मृति(म_माप(path) + म_माप(name) + 3);
		म_नकल(path2, path);
		म_जोड़ो(path2, "/");
		म_जोड़ो(path2, name);

		अगर (fnmatch(file, name, 0) == 0) अणु
			rc = पढ़ो_rom(path2);

			/*
			 * It's OK अगर the ROM is unपढ़ोable.  Maybe there
			 * is no ROM, or some other error occurred.  The
			 * important thing is that no MCA happened.
			 */
			अगर (rc > 0)
				ख_लिखो(मानक_त्रुटि, "PASS: %s read %d bytes\n", path2, rc);
			अन्यथा अणु
				ख_लिखो(मानक_त्रुटि, "PASS: %s not readable\n", path2);
				वापस rc;
			पूर्ण
		पूर्ण अन्यथा अणु
			r = lstat(path2, &buf);
			अगर (r == 0 && S_ISसूची(buf.st_mode)) अणु
				rc = scan_rom(path2, file);
				अगर (rc < 0)
					वापस rc;
			पूर्ण
		पूर्ण

		result |= rc;
		मुक्त(path2);

skip:
		मुक्त(namelist[i]);
	पूर्ण
	मुक्त(namelist);
	वापस result;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	पूर्णांक rc;

	अगर (map_mem("/dev/mem", 0, 0xA0000, 1) == 0)
		ख_लिखो(मानक_त्रुटि, "PASS: /dev/mem 0x0-0xa0000 is readable\n");
	अन्यथा
		ख_लिखो(मानक_त्रुटि, "FAIL: /dev/mem 0x0-0xa0000 not accessible\n");

	/*
	 * It's not safe to blindly पढ़ो the VGA frame buffer.  If you know
	 * how to poke the card the right way, it should respond, but it's
	 * not safe in general.  Many machines, e.g., Intel chipsets, cover
	 * up a non-responding card by just वापसing -1, but others will
	 * report the failure as a machine check.
	 */
	अगर (map_mem("/dev/mem", 0xA0000, 0x20000, 0) == 0)
		ख_लिखो(मानक_त्रुटि, "PASS: /dev/mem 0xa0000-0xc0000 is mappable\n");
	अन्यथा
		ख_लिखो(मानक_त्रुटि, "FAIL: /dev/mem 0xa0000-0xc0000 not accessible\n");

	अगर (map_mem("/dev/mem", 0xC0000, 0x40000, 1) == 0)
		ख_लिखो(मानक_त्रुटि, "PASS: /dev/mem 0xc0000-0x100000 is readable\n");
	अन्यथा
		ख_लिखो(मानक_त्रुटि, "FAIL: /dev/mem 0xc0000-0x100000 not accessible\n");

	/*
	 * Often you can map all the inभागidual pieces above (0-0xA0000,
	 * 0xA0000-0xC0000, and 0xC0000-0x100000), but can't map the whole
	 * thing at once.  This is because the inभागidual pieces use dअगरferent
	 * attributes, and there's no single attribute supported over the
	 * whole region.
	 */
	rc = map_mem("/dev/mem", 0, 1024*1024, 0);
	अगर (rc == 0)
		ख_लिखो(मानक_त्रुटि, "PASS: /dev/mem 0x0-0x100000 is mappable\n");
	अन्यथा अगर (rc > 0)
		ख_लिखो(मानक_त्रुटि, "PASS: /dev/mem 0x0-0x100000 not mappable\n");
	अन्यथा
		ख_लिखो(मानक_त्रुटि, "FAIL: /dev/mem 0x0-0x100000 not accessible\n");

	scan_tree("/sys/class/pci_bus", "legacy_mem", 0, 0xA0000, 1);
	scan_tree("/sys/class/pci_bus", "legacy_mem", 0xA0000, 0x20000, 0);
	scan_tree("/sys/class/pci_bus", "legacy_mem", 0xC0000, 0x40000, 1);
	scan_tree("/sys/class/pci_bus", "legacy_mem", 0, 1024*1024, 0);

	scan_rom("/sys/devices", "rom");

	scan_tree("/proc/bus/pci", "??.?", 0, 0xA0000, 1);
	scan_tree("/proc/bus/pci", "??.?", 0xA0000, 0x20000, 0);
	scan_tree("/proc/bus/pci", "??.?", 0xC0000, 0x40000, 1);
	scan_tree("/proc/bus/pci", "??.?", 0, 1024*1024, 0);

	वापस rc;
पूर्ण
