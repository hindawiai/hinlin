<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/fs.h>

#घोषणा DEVCG_ACC_MKNOD 1
#घोषणा DEVCG_ACC_READ  2
#घोषणा DEVCG_ACC_WRITE 4
#घोषणा DEVCG_ACC_MASK (DEVCG_ACC_MKNOD | DEVCG_ACC_READ | DEVCG_ACC_WRITE)

#घोषणा DEVCG_DEV_BLOCK 1
#घोषणा DEVCG_DEV_CHAR  2
#घोषणा DEVCG_DEV_ALL   4  /* this represents all devices */


#अगर defined(CONFIG_CGROUP_DEVICE) || defined(CONFIG_CGROUP_BPF)
पूर्णांक devcgroup_check_permission(लघु type, u32 major, u32 minor,
			       लघु access);
अटल अंतरभूत पूर्णांक devcgroup_inode_permission(काष्ठा inode *inode, पूर्णांक mask)
अणु
	लघु type, access = 0;

	अगर (likely(!inode->i_rdev))
		वापस 0;

	अगर (S_ISBLK(inode->i_mode))
		type = DEVCG_DEV_BLOCK;
	अन्यथा अगर (S_ISCHR(inode->i_mode))
		type = DEVCG_DEV_CHAR;
	अन्यथा
		वापस 0;

	अगर (mask & MAY_WRITE)
		access |= DEVCG_ACC_WRITE;
	अगर (mask & MAY_READ)
		access |= DEVCG_ACC_READ;

	वापस devcgroup_check_permission(type, imajor(inode), iminor(inode),
					  access);
पूर्ण

अटल अंतरभूत पूर्णांक devcgroup_inode_mknod(पूर्णांक mode, dev_t dev)
अणु
	लघु type;

	अगर (!S_ISBLK(mode) && !S_ISCHR(mode))
		वापस 0;

	अगर (S_ISCHR(mode) && dev == WHITEOUT_DEV)
		वापस 0;

	अगर (S_ISBLK(mode))
		type = DEVCG_DEV_BLOCK;
	अन्यथा
		type = DEVCG_DEV_CHAR;

	वापस devcgroup_check_permission(type, MAJOR(dev), MINOR(dev),
					  DEVCG_ACC_MKNOD);
पूर्ण

#अन्यथा
अटल अंतरभूत पूर्णांक devcgroup_check_permission(लघु type, u32 major, u32 minor,
			       लघु access)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक devcgroup_inode_permission(काष्ठा inode *inode, पूर्णांक mask)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक devcgroup_inode_mknod(पूर्णांक mode, dev_t dev)
अणु वापस 0; पूर्ण
#पूर्ण_अगर
