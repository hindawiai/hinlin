<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ADFS_FS_H
#घोषणा _ADFS_FS_H

#समावेश <uapi/linux/adfs_fs.h>

/*
 * Calculate the boot block checksum on an ADFS drive.  Note that this will
 * appear to be correct अगर the sector contains all zeros, so also check that
 * the disk size is non-zero!!!
 */
अटल अंतरभूत पूर्णांक adfs_checkbblk(अचिन्हित अक्षर *ptr)
अणु
	अचिन्हित पूर्णांक result = 0;
	अचिन्हित अक्षर *p = ptr + 511;

	करो अणु
	        result = (result & 0xff) + (result >> 8);
        	result = result + *--p;
	पूर्ण जबतक (p != ptr);

	वापस (result & 0xff) != ptr[511];
पूर्ण
#पूर्ण_अगर
