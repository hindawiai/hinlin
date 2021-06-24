<शैली गुरु>
/*
 * include/यंत्र-ppc/rheap.h
 *
 * Header file क्रम the implementation of a remote heap.
 *
 * Author: Pantelis Antoniou <panto@पूर्णांकracom.gr>
 *
 * 2004 (c) INTRACOM S.A. Greece. This file is licensed under
 * the terms of the GNU General Public License version 2. This program
 * is licensed "as is" without any warranty of any kind, whether express
 * or implied.
 */

#अगर_अघोषित __ASM_PPC_RHEAP_H__
#घोषणा __ASM_PPC_RHEAP_H__

#समावेश <linux/list.h>

प्रकार काष्ठा _rh_block अणु
	काष्ठा list_head list;
	अचिन्हित दीर्घ start;
	पूर्णांक size;
	स्थिर अक्षर *owner;
पूर्ण rh_block_t;

प्रकार काष्ठा _rh_info अणु
	अचिन्हित पूर्णांक alignment;
	पूर्णांक max_blocks;
	पूर्णांक empty_slots;
	rh_block_t *block;
	काष्ठा list_head empty_list;
	काष्ठा list_head मुक्त_list;
	काष्ठा list_head taken_list;
	अचिन्हित पूर्णांक flags;
पूर्ण rh_info_t;

#घोषणा RHIF_STATIC_INFO	0x1
#घोषणा RHIF_STATIC_BLOCK	0x2

प्रकार काष्ठा _rh_stats अणु
	अचिन्हित दीर्घ start;
	पूर्णांक size;
	स्थिर अक्षर *owner;
पूर्ण rh_stats_t;

#घोषणा RHGS_FREE	0
#घोषणा RHGS_TAKEN	1

/* Create a remote heap dynamically */
बाह्य rh_info_t *rh_create(अचिन्हित पूर्णांक alignment);

/* Destroy a remote heap, created by rh_create() */
बाह्य व्योम rh_destroy(rh_info_t * info);

/* Initialize in place a remote info block */
बाह्य व्योम rh_init(rh_info_t * info, अचिन्हित पूर्णांक alignment, पूर्णांक max_blocks,
		    rh_block_t * block);

/* Attach a मुक्त region to manage */
बाह्य पूर्णांक rh_attach_region(rh_info_t * info, अचिन्हित दीर्घ start, पूर्णांक size);

/* Detach a मुक्त region */
बाह्य अचिन्हित दीर्घ rh_detach_region(rh_info_t * info, अचिन्हित दीर्घ start, पूर्णांक size);

/* Allocate the given size from the remote heap (with alignment) */
बाह्य अचिन्हित दीर्घ rh_alloc_align(rh_info_t * info, पूर्णांक size, पूर्णांक alignment,
		स्थिर अक्षर *owner);

/* Allocate the given size from the remote heap */
बाह्य अचिन्हित दीर्घ rh_alloc(rh_info_t * info, पूर्णांक size, स्थिर अक्षर *owner);

/* Allocate the given size from the given address */
बाह्य अचिन्हित दीर्घ rh_alloc_fixed(rh_info_t * info, अचिन्हित दीर्घ start, पूर्णांक size,
			    स्थिर अक्षर *owner);

/* Free the allocated area */
बाह्य पूर्णांक rh_मुक्त(rh_info_t * info, अचिन्हित दीर्घ start);

/* Get stats क्रम debugging purposes */
बाह्य पूर्णांक rh_get_stats(rh_info_t * info, पूर्णांक what, पूर्णांक max_stats,
			rh_stats_t * stats);

/* Simple dump of remote heap info */
बाह्य व्योम rh_dump(rh_info_t * info);

/* Simple dump of remote info block */
व्योम rh_dump_blk(rh_info_t *info, rh_block_t *blk);

/* Set owner of taken block */
बाह्य पूर्णांक rh_set_owner(rh_info_t * info, अचिन्हित दीर्घ start, स्थिर अक्षर *owner);

#पूर्ण_अगर				/* __ASM_PPC_RHEAP_H__ */
