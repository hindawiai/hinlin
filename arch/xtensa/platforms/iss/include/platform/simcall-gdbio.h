<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2021 Cadence Design Systems Inc. */

#अगर_अघोषित _XTENSA_PLATFORM_ISS_SIMCALL_GDBIO_H
#घोषणा _XTENSA_PLATFORM_ISS_SIMCALL_GDBIO_H

/*
 *  System call like services offered by the GDBIO host.
 */

#घोषणा SYS_खोलो	-2
#घोषणा SYS_बंद	-3
#घोषणा SYS_पढ़ो	-4
#घोषणा SYS_ग_लिखो	-5
#घोषणा SYS_lseek	-6

अटल पूर्णांक त्रुटि_सं;

अटल अंतरभूत पूर्णांक __simc(पूर्णांक a, पूर्णांक b, पूर्णांक c, पूर्णांक d)
अणु
	रेजिस्टर पूर्णांक a1 यंत्र("a2") = a;
	रेजिस्टर पूर्णांक b1 यंत्र("a6") = b;
	रेजिस्टर पूर्णांक c1 यंत्र("a3") = c;
	रेजिस्टर पूर्णांक d1 यंत्र("a4") = d;
	__यंत्र__ __अस्थिर__ (
			"break 1, 14\n"
			: "+r"(a1), "+r"(c1)
			: "r"(b1), "r"(d1)
			: "memory");
	त्रुटि_सं = c1;
	वापस a1;
पूर्ण

#पूर्ण_अगर /* _XTENSA_PLATFORM_ISS_SIMCALL_GDBIO_H */
