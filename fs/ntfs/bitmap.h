<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * biपंचांगap.h - Defines क्रम NTFS kernel biपंचांगap handling.  Part of the Linux-NTFS
 *	      project.
 *
 * Copyright (c) 2004 Anton Altaparmakov
 */

#अगर_अघोषित _LINUX_NTFS_BITMAP_H
#घोषणा _LINUX_NTFS_BITMAP_H

#अगर_घोषित NTFS_RW

#समावेश <linux/fs.h>

#समावेश "types.h"

बाह्य पूर्णांक __ntfs_biपंचांगap_set_bits_in_run(काष्ठा inode *vi, स्थिर s64 start_bit,
		स्थिर s64 count, स्थिर u8 value, स्थिर bool is_rollback);

/**
 * ntfs_biपंचांगap_set_bits_in_run - set a run of bits in a biपंचांगap to a value
 * @vi:			vfs inode describing the biपंचांगap
 * @start_bit:		first bit to set
 * @count:		number of bits to set
 * @value:		value to set the bits to (i.e. 0 or 1)
 *
 * Set @count bits starting at bit @start_bit in the biपंचांगap described by the
 * vfs inode @vi to @value, where @value is either 0 or 1.
 *
 * Return 0 on success and -त्रुटि_सं on error.
 */
अटल अंतरभूत पूर्णांक ntfs_biपंचांगap_set_bits_in_run(काष्ठा inode *vi,
		स्थिर s64 start_bit, स्थिर s64 count, स्थिर u8 value)
अणु
	वापस __ntfs_biपंचांगap_set_bits_in_run(vi, start_bit, count, value,
			false);
पूर्ण

/**
 * ntfs_biपंचांगap_set_run - set a run of bits in a biपंचांगap
 * @vi:		vfs inode describing the biपंचांगap
 * @start_bit:	first bit to set
 * @count:	number of bits to set
 *
 * Set @count bits starting at bit @start_bit in the biपंचांगap described by the
 * vfs inode @vi.
 *
 * Return 0 on success and -त्रुटि_सं on error.
 */
अटल अंतरभूत पूर्णांक ntfs_biपंचांगap_set_run(काष्ठा inode *vi, स्थिर s64 start_bit,
		स्थिर s64 count)
अणु
	वापस ntfs_biपंचांगap_set_bits_in_run(vi, start_bit, count, 1);
पूर्ण

/**
 * ntfs_biपंचांगap_clear_run - clear a run of bits in a biपंचांगap
 * @vi:		vfs inode describing the biपंचांगap
 * @start_bit:	first bit to clear
 * @count:	number of bits to clear
 *
 * Clear @count bits starting at bit @start_bit in the biपंचांगap described by the
 * vfs inode @vi.
 *
 * Return 0 on success and -त्रुटि_सं on error.
 */
अटल अंतरभूत पूर्णांक ntfs_biपंचांगap_clear_run(काष्ठा inode *vi, स्थिर s64 start_bit,
		स्थिर s64 count)
अणु
	वापस ntfs_biपंचांगap_set_bits_in_run(vi, start_bit, count, 0);
पूर्ण

/**
 * ntfs_biपंचांगap_set_bit - set a bit in a biपंचांगap
 * @vi:		vfs inode describing the biपंचांगap
 * @bit:	bit to set
 *
 * Set bit @bit in the biपंचांगap described by the vfs inode @vi.
 *
 * Return 0 on success and -त्रुटि_सं on error.
 */
अटल अंतरभूत पूर्णांक ntfs_biपंचांगap_set_bit(काष्ठा inode *vi, स्थिर s64 bit)
अणु
	वापस ntfs_biपंचांगap_set_run(vi, bit, 1);
पूर्ण

/**
 * ntfs_biपंचांगap_clear_bit - clear a bit in a biपंचांगap
 * @vi:		vfs inode describing the biपंचांगap
 * @bit:	bit to clear
 *
 * Clear bit @bit in the biपंचांगap described by the vfs inode @vi.
 *
 * Return 0 on success and -त्रुटि_सं on error.
 */
अटल अंतरभूत पूर्णांक ntfs_biपंचांगap_clear_bit(काष्ठा inode *vi, स्थिर s64 bit)
अणु
	वापस ntfs_biपंचांगap_clear_run(vi, bit, 1);
पूर्ण

#पूर्ण_अगर /* NTFS_RW */

#पूर्ण_अगर /* defined _LINUX_NTFS_BITMAP_H */
