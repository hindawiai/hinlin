<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000,2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित	__XFS_EXTFREE_ITEM_H__
#घोषणा	__XFS_EXTFREE_ITEM_H__

/* kernel only EFI/EFD definitions */

काष्ठा xfs_mount;
काष्ठा kmem_zone;

/*
 * Max number of extents in fast allocation path.
 */
#घोषणा	XFS_EFI_MAX_FAST_EXTENTS	16

/*
 * This is the "extent free intention" log item.  It is used to log the fact
 * that some extents need to be मुक्त.  It is used in conjunction with the
 * "extent free done" log item described below.
 *
 * The EFI is reference counted so that it is not मुक्तd prior to both the EFI
 * and EFD being committed and unpinned. This ensures the EFI is inserted पूर्णांकo
 * the AIL even in the event of out of order EFI/EFD processing. In other words,
 * an EFI is born with two references:
 *
 * 	1.) an EFI held reference to track EFI AIL insertion
 * 	2.) an EFD held reference to track EFD commit
 *
 * On allocation, both references are the responsibility of the caller. Once the
 * EFI is added to and dirtied in a transaction, ownership of reference one
 * transfers to the transaction. The reference is dropped once the EFI is
 * inserted to the AIL or in the event of failure aदीर्घ the way (e.g., commit
 * failure, log I/O error, etc.). Note that the caller reमुख्यs responsible क्रम
 * the EFD reference under all circumstances to this poपूर्णांक. The caller has no
 * means to detect failure once the transaction is committed, however.
 * Thereक्रमe, an EFD is required after this poपूर्णांक, even in the event of
 * unrelated failure.
 *
 * Once an EFD is allocated and dirtied in a transaction, reference two
 * transfers to the transaction. The EFD reference is dropped once it reaches
 * the unpin handler. Similar to the EFI, the reference also drops in the event
 * of commit failure or log I/O errors. Note that the EFD is not inserted in the
 * AIL, so at this poपूर्णांक both the EFI and EFD are मुक्तd.
 */
काष्ठा xfs_efi_log_item अणु
	काष्ठा xfs_log_item	efi_item;
	atomic_t		efi_refcount;
	atomic_t		efi_next_extent;
	xfs_efi_log_क्रमmat_t	efi_क्रमmat;
पूर्ण;

/*
 * This is the "extent free done" log item.  It is used to log
 * the fact that some extents earlier mentioned in an efi item
 * have been मुक्तd.
 */
काष्ठा xfs_efd_log_item अणु
	काष्ठा xfs_log_item	efd_item;
	काष्ठा xfs_efi_log_item *efd_efip;
	uपूर्णांक			efd_next_extent;
	xfs_efd_log_क्रमmat_t	efd_क्रमmat;
पूर्ण;

/*
 * Max number of extents in fast allocation path.
 */
#घोषणा	XFS_EFD_MAX_FAST_EXTENTS	16

बाह्य काष्ठा kmem_zone	*xfs_efi_zone;
बाह्य काष्ठा kmem_zone	*xfs_efd_zone;

#पूर्ण_अगर	/* __XFS_EXTFREE_ITEM_H__ */
