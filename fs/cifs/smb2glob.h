<शैली गुरु>
/*
 *   fs/cअगरs/smb2glob.h
 *
 *   Definitions क्रम various global variables and काष्ठाures
 *
 *   Copyright (C) International Business Machines  Corp., 2002, 2011
 *                 Etersoft, 2012
 *   Author(s): Steve French (sfrench@us.ibm.com)
 *              Jeremy Allison (jra@samba.org)
 *              Pavel Shilovsky (pshilovsky@samba.org) 2012
 *
 *   This library is मुक्त software; you can redistribute it and/or modअगरy
 *   it under the terms of the GNU Lesser General Public License as published
 *   by the Free Software Foundation; either version 2.1 of the License, or
 *   (at your option) any later version.
 *
 *   This library is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
 *   the GNU Lesser General Public License क्रम more details.
 *
 */
#अगर_अघोषित _SMB2_GLOB_H
#घोषणा _SMB2_GLOB_H

#घोषणा SMB2_MAGIC_NUMBER 0xFE534D42

/*
 *****************************************************************
 * Constants go here
 *****************************************************************
 */

/*
 * Identअगरiers क्रम functions that use the खोलो, operation, बंद pattern
 * in smb2inode.c:smb2_compound_op()
 */
#घोषणा SMB2_OP_SET_DELETE 1
#घोषणा SMB2_OP_SET_INFO 2
#घोषणा SMB2_OP_QUERY_INFO 3
#घोषणा SMB2_OP_QUERY_सूची 4
#घोषणा SMB2_OP_MKसूची 5
#घोषणा SMB2_OP_RENAME 6
#घोषणा SMB2_OP_DELETE 7
#घोषणा SMB2_OP_HARDLINK 8
#घोषणा SMB2_OP_SET_खातापूर्ण 9
#घोषणा SMB2_OP_RMसूची 10
#घोषणा SMB2_OP_POSIX_QUERY_INFO 11

/* Used when स्थिरructing chained पढ़ो requests. */
#घोषणा CHAINED_REQUEST 1
#घोषणा START_OF_CHAIN 2
#घोषणा END_OF_CHAIN 4
#घोषणा RELATED_REQUEST 8

#घोषणा SMB2_SIGNATURE_SIZE (16)
#घोषणा SMB2_NTLMV2_SESSKEY_SIZE (16)
#घोषणा SMB2_HMACSHA256_SIZE (32)
#घोषणा SMB2_CMACAES_SIZE (16)
#घोषणा SMB3_SIGNKEY_SIZE (16)
#घोषणा SMB3_GCM128_CRYPTKEY_SIZE (16)
#घोषणा SMB3_GCM256_CRYPTKEY_SIZE (32)

/* Maximum buffer size value we can send with 1 credit */
#घोषणा SMB2_MAX_BUFFER_SIZE 65536

#पूर्ण_अगर	/* _SMB2_GLOB_H */
