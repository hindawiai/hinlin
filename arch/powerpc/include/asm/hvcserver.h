<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * hvcserver.h
 * Copyright (C) 2004 Ryan S Arnold, IBM Corporation
 *
 * PPC64 भव I/O console server support.
 */

#अगर_अघोषित _PPC64_HVCSERVER_H
#घोषणा _PPC64_HVCSERVER_H
#अगर_घोषित __KERNEL__

#समावेश <linux/list.h>

/* Converged Location Code length */
#घोषणा HVCS_CLC_LENGTH	79

/**
 * hvcs_partner_info - an element in a list of partner info
 * @node: list_head denoting this partner_info काष्ठा's position in the list of
 *	partner info.
 * @unit_address: The partner unit address of this entry.
 * @partition_ID: The partner partition ID of this entry.
 * @location_code: The converged location code of this entry + 1 अक्षर क्रम the
 *	null-term.
 *
 * This काष्ठाure outlines the क्रमmat that partner info is presented to a caller
 * of the hvcs partner info fetching functions.  These are strung together पूर्णांकo
 * a list using linux kernel lists.
 */
काष्ठा hvcs_partner_info अणु
	काष्ठा list_head node;
	uपूर्णांक32_t unit_address;
	uपूर्णांक32_t partition_ID;
	अक्षर location_code[HVCS_CLC_LENGTH + 1]; /* CLC + 1 null-term अक्षर */
पूर्ण;

बाह्य पूर्णांक hvcs_मुक्त_partner_info(काष्ठा list_head *head);
बाह्य पूर्णांक hvcs_get_partner_info(uपूर्णांक32_t unit_address,
		काष्ठा list_head *head, अचिन्हित दीर्घ *pi_buff);
बाह्य पूर्णांक hvcs_रेजिस्टर_connection(uपूर्णांक32_t unit_address,
		uपूर्णांक32_t p_partition_ID, uपूर्णांक32_t p_unit_address);
बाह्य पूर्णांक hvcs_मुक्त_connection(uपूर्णांक32_t unit_address);

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _PPC64_HVCSERVER_H */
