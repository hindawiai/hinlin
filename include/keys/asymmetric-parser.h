<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* Asymmetric खुला-key cryptography data parser
 *
 * See Documentation/crypto/asymmetric-keys.rst
 *
 * Copyright (C) 2012 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#अगर_अघोषित _KEYS_ASYMMETRIC_PARSER_H
#घोषणा _KEYS_ASYMMETRIC_PARSER_H

/*
 * Key data parser.  Called during key instantiation.
 */
काष्ठा asymmetric_key_parser अणु
	काष्ठा list_head	link;
	काष्ठा module		*owner;
	स्थिर अक्षर		*name;

	/* Attempt to parse a key from the data blob passed to add_key() or
	 * keyctl_instantiate().  Should also generate a proposed description
	 * that the caller can optionally use क्रम the key.
	 *
	 * Return EBADMSG अगर not recognised.
	 */
	पूर्णांक (*parse)(काष्ठा key_preparsed_payload *prep);
पूर्ण;

बाह्य पूर्णांक रेजिस्टर_asymmetric_key_parser(काष्ठा asymmetric_key_parser *);
बाह्य व्योम unरेजिस्टर_asymmetric_key_parser(काष्ठा asymmetric_key_parser *);

#पूर्ण_अगर /* _KEYS_ASYMMETRIC_PARSER_H */
