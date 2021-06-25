<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _XT_SCTP_H_
#घोषणा _XT_SCTP_H_

#समावेश <linux/types.h>

#घोषणा XT_SCTP_SRC_PORTS	        0x01
#घोषणा XT_SCTP_DEST_PORTS	        0x02
#घोषणा XT_SCTP_CHUNK_TYPES		0x04

#घोषणा XT_SCTP_VALID_FLAGS		0x07

काष्ठा xt_sctp_flag_info अणु
	__u8 chunktype;
	__u8 flag;
	__u8 flag_mask;
पूर्ण;

#घोषणा XT_NUM_SCTP_FLAGS	4

काष्ठा xt_sctp_info अणु
	__u16 dpts[2];  /* Min, Max */
	__u16 spts[2];  /* Min, Max */

	__u32 chunkmap[256 / माप (__u32)];  /* Bit mask of chunks to be matched according to RFC 2960 */

#घोषणा SCTP_CHUNK_MATCH_ANY   0x01  /* Match अगर any of the chunk types are present */
#घोषणा SCTP_CHUNK_MATCH_ALL   0x02  /* Match अगर all of the chunk types are present */
#घोषणा SCTP_CHUNK_MATCH_ONLY  0x04  /* Match अगर these are the only chunk types present */

	__u32 chunk_match_type;
	काष्ठा xt_sctp_flag_info flag_info[XT_NUM_SCTP_FLAGS];
	पूर्णांक flag_count;

	__u32 flags;
	__u32 invflags;
पूर्ण;

#घोषणा bytes(type) (माप(type) * 8)

#घोषणा SCTP_CHUNKMAP_SET(chunkmap, type) 		\
	करो अणु 						\
		(chunkmap)[type / bytes(__u32)] |= 	\
			1u << (type % bytes(__u32));	\
	पूर्ण जबतक (0)

#घोषणा SCTP_CHUNKMAP_CLEAR(chunkmap, type)		 	\
	करो अणु							\
		(chunkmap)[type / bytes(__u32)] &= 		\
			~(1u << (type % bytes(__u32)));	\
	पूर्ण जबतक (0)

#घोषणा SCTP_CHUNKMAP_IS_SET(chunkmap, type) 			\
(अणु								\
	((chunkmap)[type / bytes (__u32)] & 		\
		(1u << (type % bytes (__u32)))) ? 1: 0;	\
पूर्ण)

#घोषणा SCTP_CHUNKMAP_RESET(chunkmap) \
	स_रखो((chunkmap), 0, माप(chunkmap))

#घोषणा SCTP_CHUNKMAP_SET_ALL(chunkmap) \
	स_रखो((chunkmap), ~0U, माप(chunkmap))

#घोषणा SCTP_CHUNKMAP_COPY(desपंचांगap, srcmap) \
	स_नकल((desपंचांगap), (srcmap), माप(srcmap))

#घोषणा SCTP_CHUNKMAP_IS_CLEAR(chunkmap) \
	__sctp_chunkmap_is_clear((chunkmap), ARRAY_SIZE(chunkmap))
अटल अंतरभूत _Bool
__sctp_chunkmap_is_clear(स्थिर __u32 *chunkmap, अचिन्हित पूर्णांक n)
अणु
	अचिन्हित पूर्णांक i;
	क्रम (i = 0; i < n; ++i)
		अगर (chunkmap[i])
			वापस 0;
	वापस 1;
पूर्ण

#घोषणा SCTP_CHUNKMAP_IS_ALL_SET(chunkmap) \
	__sctp_chunkmap_is_all_set((chunkmap), ARRAY_SIZE(chunkmap))
अटल अंतरभूत _Bool
__sctp_chunkmap_is_all_set(स्थिर __u32 *chunkmap, अचिन्हित पूर्णांक n)
अणु
	अचिन्हित पूर्णांक i;
	क्रम (i = 0; i < n; ++i)
		अगर (chunkmap[i] != ~0U)
			वापस 0;
	वापस 1;
पूर्ण

#पूर्ण_अगर /* _XT_SCTP_H_ */

