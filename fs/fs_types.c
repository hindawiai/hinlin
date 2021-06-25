<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/fs.h>
#समावेश <linux/export.h>

/*
 * fs on-disk file type to dirent file type conversion
 */
अटल स्थिर अचिन्हित अक्षर fs_dtype_by_ftype[FT_MAX] = अणु
	[FT_UNKNOWN]	= DT_UNKNOWN,
	[FT_REG_खाता]	= DT_REG,
	[FT_सूची]	= DT_सूची,
	[FT_CHRDEV]	= DT_CHR,
	[FT_BLKDEV]	= DT_BLK,
	[FT_FIFO]	= DT_FIFO,
	[FT_SOCK]	= DT_SOCK,
	[FT_SYMLINK]	= DT_LNK
पूर्ण;

/**
 * fs_ftype_to_dtype() - fs on-disk file type to dirent type.
 * @filetype: The on-disk file type to convert.
 *
 * This function converts the on-disk file type value (FT_*) to the directory
 * entry type (DT_*).
 *
 * Context: Any context.
 * Return:
 * * DT_UNKNOWN		- Unknown type
 * * DT_FIFO		- FIFO
 * * DT_CHR		- Character device
 * * DT_सूची		- Directory
 * * DT_BLK		- Block device
 * * DT_REG		- Regular file
 * * DT_LNK		- Symbolic link
 * * DT_SOCK		- Local-करोमुख्य socket
 */
अचिन्हित अक्षर fs_ftype_to_dtype(अचिन्हित पूर्णांक filetype)
अणु
	अगर (filetype >= FT_MAX)
		वापस DT_UNKNOWN;

	वापस fs_dtype_by_ftype[filetype];
पूर्ण
EXPORT_SYMBOL_GPL(fs_ftype_to_dtype);

/*
 * dirent file type to fs on-disk file type conversion
 * Values not initialized explicitly are FT_UNKNOWN (0).
 */
अटल स्थिर अचिन्हित अक्षर fs_ftype_by_dtype[DT_MAX] = अणु
	[DT_REG]	= FT_REG_खाता,
	[DT_सूची]	= FT_सूची,
	[DT_LNK]	= FT_SYMLINK,
	[DT_CHR]	= FT_CHRDEV,
	[DT_BLK]	= FT_BLKDEV,
	[DT_FIFO]	= FT_FIFO,
	[DT_SOCK]	= FT_SOCK,
पूर्ण;

/**
 * fs_umode_to_ftype() - file mode to on-disk file type.
 * @mode: The file mode to convert.
 *
 * This function converts the file mode value to the on-disk file type (FT_*).
 *
 * Context: Any context.
 * Return:
 * * FT_UNKNOWN		- Unknown type
 * * FT_REG_खाता	- Regular file
 * * FT_सूची		- Directory
 * * FT_CHRDEV		- Character device
 * * FT_BLKDEV		- Block device
 * * FT_FIFO		- FIFO
 * * FT_SOCK		- Local-करोमुख्य socket
 * * FT_SYMLINK		- Symbolic link
 */
अचिन्हित अक्षर fs_umode_to_ftype(umode_t mode)
अणु
	वापस fs_ftype_by_dtype[S_DT(mode)];
पूर्ण
EXPORT_SYMBOL_GPL(fs_umode_to_ftype);

/**
 * fs_umode_to_dtype() - file mode to dirent file type.
 * @mode: The file mode to convert.
 *
 * This function converts the file mode value to the directory
 * entry type (DT_*).
 *
 * Context: Any context.
 * Return:
 * * DT_UNKNOWN		- Unknown type
 * * DT_FIFO		- FIFO
 * * DT_CHR		- Character device
 * * DT_सूची		- Directory
 * * DT_BLK		- Block device
 * * DT_REG		- Regular file
 * * DT_LNK		- Symbolic link
 * * DT_SOCK		- Local-करोमुख्य socket
 */
अचिन्हित अक्षर fs_umode_to_dtype(umode_t mode)
अणु
	वापस fs_ftype_to_dtype(fs_umode_to_ftype(mode));
पूर्ण
EXPORT_SYMBOL_GPL(fs_umode_to_dtype);
