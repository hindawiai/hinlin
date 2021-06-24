<शैली गुरु>
/*
 * include/uapi/linux/nfs_idmap.h
 *
 *  UID and GID to name mapping क्रम clients.
 *
 *  Copyright (c) 2002 The Regents of the University of Michigan.
 *  All rights reserved.
 *
 *  Marius Aamodt Eriksen <marius@umich.edu>
 *
 *  Redistribution and use in source and binary क्रमms, with or without
 *  modअगरication, are permitted provided that the following conditions
 *  are met:
 *
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary क्रमm must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     करोcumentation and/or other materials provided with the distribution.
 *  3. Neither the name of the University nor the names of its
 *     contributors may be used to enकरोrse or promote products derived
 *     from this software without specअगरic prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
 *  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 *  FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 *  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 *  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#अगर_अघोषित _UAPINFS_IDMAP_H
#घोषणा _UAPINFS_IDMAP_H

#समावेश <linux/types.h>

/* XXX from bits/uपंचांगp.h  */
#घोषणा IDMAP_NAMESZ  128

#घोषणा IDMAP_TYPE_USER  0
#घोषणा IDMAP_TYPE_GROUP 1

#घोषणा IDMAP_CONV_IDTONAME 0
#घोषणा IDMAP_CONV_NAMETOID 1

#घोषणा IDMAP_STATUS_INVALIDMSG 0x01
#घोषणा IDMAP_STATUS_AGAIN      0x02
#घोषणा IDMAP_STATUS_LOOKUPFAIL 0x04
#घोषणा IDMAP_STATUS_SUCCESS    0x08

काष्ठा idmap_msg अणु
	__u8  im_type;
	__u8  im_conv;
	अक्षर  im_name[IDMAP_NAMESZ];
	__u32 im_id;
	__u8  im_status;
पूर्ण;


#पूर्ण_अगर /* _UAPINFS_IDMAP_H */
