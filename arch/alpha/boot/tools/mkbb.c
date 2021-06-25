<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* This utility makes a bootblock suitable क्रम the SRM console/miniloader */

/* Usage:
 *	mkbb <device> <lxboot>
 *
 * Where <device> is the name of the device to install the bootblock on,
 * and <lxboot> is the name of a bootblock to merge in.  This bootblock
 * contains the offset and size of the bootloader.  It must be exactly
 * 512 bytes दीर्घ.
 */

#समावेश <fcntl.h>
#समावेश <unistd.h>
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>

/* Minimal definition of disklabel, so we करोn't have to include
 * यंत्र/disklabel.h (confuses make)
 */
#अगर_अघोषित MAXPARTITIONS
#घोषणा MAXPARTITIONS   8                       /* max. # of partitions */
#पूर्ण_अगर

#अगर_अघोषित u8
#घोषणा u8 अचिन्हित अक्षर
#पूर्ण_अगर

#अगर_अघोषित u16
#घोषणा u16 अचिन्हित लघु
#पूर्ण_अगर

#अगर_अघोषित u32
#घोषणा u32 अचिन्हित पूर्णांक
#पूर्ण_अगर

काष्ठा disklabel अणु
    u32	d_magic;				/* must be DISKLABELMAGIC */
    u16	d_type, d_subtype;
    u8	d_typename[16];
    u8	d_packname[16];
    u32	d_secsize;
    u32	d_nsectors;
    u32	d_ntracks;
    u32	d_ncylinders;
    u32	d_secpercyl;
    u32	d_secprtunit;
    u16	d_sparespertrack;
    u16	d_sparespercyl;
    u32	d_acylinders;
    u16	d_rpm, d_पूर्णांकerleave, d_trackskew, d_cylskew;
    u32	d_headचयन, d_trkseek, d_flags;
    u32	d_drivedata[5];
    u32	d_spare[5];
    u32	d_magic2;				/* must be DISKLABELMAGIC */
    u16	d_checksum;
    u16	d_npartitions;
    u32	d_bbsize, d_sbsize;
    काष्ठा d_partition अणु
	u32	p_size;
	u32	p_offset;
	u32	p_fsize;
	u8	p_fstype;
	u8	p_frag;
	u16	p_cpg;
    पूर्ण d_partitions[MAXPARTITIONS];
पूर्ण;


प्रकार जोड़ __bootblock अणु
    काष्ठा अणु
        अक्षर			__pad1[64];
        काष्ठा disklabel	__label;
    पूर्ण __u1;
    काष्ठा अणु
	अचिन्हित दीर्घ		__pad2[63];
	अचिन्हित दीर्घ		__checksum;
    पूर्ण __u2;
    अक्षर		bootblock_bytes[512];
    अचिन्हित दीर्घ	bootblock_quadwords[64];
पूर्ण bootblock;

#घोषणा	bootblock_label		__u1.__label
#घोषणा bootblock_checksum	__u2.__checksum

पूर्णांक मुख्य(पूर्णांक argc, अक्षर ** argv)
अणु
    bootblock		bootblock_from_disk;
    bootblock		bootloader_image;
    पूर्णांक			dev, fd;
    पूर्णांक			i;
    पूर्णांक			nपढ़ो;

    /* Make sure of the arg count */
    अगर(argc != 3) अणु
	ख_लिखो(मानक_त्रुटि, "Usage: %s device lxboot\n", argv[0]);
	निकास(0);
    पूर्ण

    /* First, खोलो the device and make sure it's accessible */
    dev = खोलो(argv[1], O_RDWR);
    अगर(dev < 0) अणु
	लिखो_त्रुटि(argv[1]);
	निकास(0);
    पूर्ण

    /* Now खोलो the lxboot and make sure it's reasonable */
    fd = खोलो(argv[2], O_RDONLY);
    अगर(fd < 0) अणु
	लिखो_त्रुटि(argv[2]);
	बंद(dev);
	निकास(0);
    पूर्ण

    /* Read in the lxboot */
    nपढ़ो = पढ़ो(fd, &bootloader_image, माप(bootblock));
    अगर(nपढ़ो != माप(bootblock)) अणु
	लिखो_त्रुटि("lxboot read");
	ख_लिखो(मानक_त्रुटि, "expected %zd, got %d\n", माप(bootblock), nपढ़ो);
	निकास(0);
    पूर्ण

    /* Read in the bootblock from disk. */
    nपढ़ो = पढ़ो(dev, &bootblock_from_disk, माप(bootblock));
    अगर(nपढ़ो != माप(bootblock)) अणु
	लिखो_त्रुटि("bootblock read");
	ख_लिखो(मानक_त्रुटि, "expected %zd, got %d\n", माप(bootblock), nपढ़ो);
	निकास(0);
    पूर्ण

    /* Swap the bootblock's disklabel पूर्णांकo the bootloader */
    bootloader_image.bootblock_label = bootblock_from_disk.bootblock_label;

    /* Calculate the bootblock checksum */
    bootloader_image.bootblock_checksum = 0;
    क्रम(i = 0; i < 63; i++) अणु
	bootloader_image.bootblock_checksum += 
			bootloader_image.bootblock_quadwords[i];
    पूर्ण

    /* Write the whole thing out! */
    lseek(dev, 0L, शुरू_से);
    अगर(ग_लिखो(dev, &bootloader_image, माप(bootblock)) != माप(bootblock)) अणु
	लिखो_त्रुटि("bootblock write");
	निकास(0);
    पूर्ण

    बंद(fd);
    बंद(dev);
    निकास(0);
पूर्ण


