<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2010-2011, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _ASM_CHECKSUM_H
#घोषणा _ASM_CHECKSUM_H

#घोषणा करो_csum	करो_csum
अचिन्हित पूर्णांक करो_csum(स्थिर व्योम *व्योमptr, पूर्णांक len);

/*
 * computes the checksum of the TCP/UDP pseuकरो-header
 * वापसs a 16-bit checksum, alपढ़ोy complemented
 */
#घोषणा csum_tcpudp_nofold csum_tcpudp_nofold
__wsum csum_tcpudp_nofold(__be32 saddr, __be32 daddr,
			  __u32 len, __u8 proto, __wsum sum);

#घोषणा csum_tcpudp_magic csum_tcpudp_magic
__sum16 csum_tcpudp_magic(__be32 saddr, __be32 daddr,
			  __u32 len, __u8 proto, __wsum sum);

#समावेश <यंत्र-generic/checksum.h>

#पूर्ण_अगर
