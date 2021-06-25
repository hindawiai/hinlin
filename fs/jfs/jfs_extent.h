<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *   Copyright (C) International Business Machines Corp., 2000-2001
 */
#अगर_अघोषित	_H_JFS_EXTENT
#घोषणा _H_JFS_EXTENT

/*  get block allocation hपूर्णांक as location of disk inode */
#घोषणा	INOHINT(ip)	\
	(addressPXD(&(JFS_IP(ip)->ixpxd)) + lengthPXD(&(JFS_IP(ip)->ixpxd)) - 1)

बाह्य पूर्णांक	extAlloc(काष्ठा inode *, s64, s64, xad_t *, bool);
बाह्य पूर्णांक	extFill(काष्ठा inode *, xad_t *);
बाह्य पूर्णांक	extHपूर्णांक(काष्ठा inode *, s64, xad_t *);
बाह्य पूर्णांक	extRealloc(काष्ठा inode *, s64, xad_t *, bool);
बाह्य पूर्णांक	extRecord(काष्ठा inode *, xad_t *);

#पूर्ण_अगर	/* _H_JFS_EXTENT */
