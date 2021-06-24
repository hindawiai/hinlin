<शैली गुरु>
/******************************************************************************
 * gntभाग.स
 *
 * Interface to /dev/xen/gntalloc.
 *
 * Author: Daniel De Graaf <dgdegra@tycho.nsa.gov>
 *
 * This file is in the खुला करोमुख्य.
 */

#अगर_अघोषित __LINUX_PUBLIC_GNTALLOC_H__
#घोषणा __LINUX_PUBLIC_GNTALLOC_H__

#समावेश <linux/types.h>

/*
 * Allocates a new page and creates a new grant reference.
 */
#घोषणा IOCTL_GNTALLOC_ALLOC_GREF \
_IOC(_IOC_NONE, 'G', 5, माप(काष्ठा ioctl_gntalloc_alloc_gref))
काष्ठा ioctl_gntalloc_alloc_gref अणु
	/* IN parameters */
	/* The ID of the करोमुख्य to be given access to the grants. */
	__u16 करोmid;
	/* Flags क्रम this mapping */
	__u16 flags;
	/* Number of pages to map */
	__u32 count;
	/* OUT parameters */
	/* The offset to be used on a subsequent call to mmap(). */
	__u64 index;
	/* The grant references of the newly created grant, one per page */
	/* Variable size, depending on count */
	__u32 gref_ids[1];
पूर्ण;

#घोषणा GNTALLOC_FLAG_WRITABLE 1

/*
 * Deallocates the grant reference, allowing the associated page to be मुक्तd अगर
 * no other करोमुख्यs are using it.
 */
#घोषणा IOCTL_GNTALLOC_DEALLOC_GREF \
_IOC(_IOC_NONE, 'G', 6, माप(काष्ठा ioctl_gntalloc_dealloc_gref))
काष्ठा ioctl_gntalloc_dealloc_gref अणु
	/* IN parameters */
	/* The offset वापसed in the map operation */
	__u64 index;
	/* Number of references to unmap */
	__u32 count;
पूर्ण;

/*
 * Sets up an unmap notअगरication within the page, so that the other side can करो
 * cleanup अगर this side crashes. Required to implement cross-करोमुख्य robust
 * mutexes or बंद notअगरication on communication channels.
 *
 * Each mapped page only supports one notअगरication; multiple calls referring to
 * the same page overग_लिखो the previous notअगरication. You must clear the
 * notअगरication prior to the IOCTL_GNTALLOC_DEALLOC_GREF अगर you करो not want it
 * to occur.
 */
#घोषणा IOCTL_GNTALLOC_SET_UNMAP_NOTIFY \
_IOC(_IOC_NONE, 'G', 7, माप(काष्ठा ioctl_gntalloc_unmap_notअगरy))
काष्ठा ioctl_gntalloc_unmap_notअगरy अणु
	/* IN parameters */
	/* Offset in the file descriptor क्रम a byte within the page (same as
	 * used in mmap). If using UNMAP_NOTIFY_CLEAR_BYTE, this is the byte to
	 * be cleared. Otherwise, it can be any byte in the page whose
	 * notअगरication we are adjusting.
	 */
	__u64 index;
	/* Action(s) to take on unmap */
	__u32 action;
	/* Event channel to notअगरy */
	__u32 event_channel_port;
पूर्ण;

/* Clear (set to zero) the byte specअगरied by index */
#घोषणा UNMAP_NOTIFY_CLEAR_BYTE 0x1
/* Send an पूर्णांकerrupt on the indicated event channel */
#घोषणा UNMAP_NOTIFY_SEND_EVENT 0x2

#पूर्ण_अगर /* __LINUX_PUBLIC_GNTALLOC_H__ */
