<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Definitions क्रम building a device tree by calling पूर्णांकo the
 * Open Firmware PROM.
 *
 * Copyright (C) 2010  Andres Salomon <dilinger@queued.net>
 */

#अगर_अघोषित _LINUX_OF_PDT_H
#घोषणा _LINUX_OF_PDT_H

/* overridable operations क्रम calling पूर्णांकo the PROM */
काष्ठा of_pdt_ops अणु
	/*
	 * buf should be 32 bytes; वापस 0 on success.
	 * If prev is शून्य, the first property will be वापसed.
	 */
	पूर्णांक (*nextprop)(phandle node, अक्षर *prev, अक्षर *buf);

	/* क्रम both functions, वापस proplen on success; -1 on error */
	पूर्णांक (*getproplen)(phandle node, स्थिर अक्षर *prop);
	पूर्णांक (*getproperty)(phandle node, स्थिर अक्षर *prop, अक्षर *buf,
			पूर्णांक bufsize);

	/* phandles are 0 अगर no child or sibling exists */
	phandle (*अ_लोhild)(phandle parent);
	phandle (*माला_लोibling)(phandle node);

	/* वापस 0 on success; fill in 'len' with number of bytes in path */
	पूर्णांक (*pkg2path)(phandle node, अक्षर *buf, स्थिर पूर्णांक buflen, पूर्णांक *len);
पूर्ण;

बाह्य व्योम *prom_early_alloc(अचिन्हित दीर्घ size);

/* क्रम building the device tree */
बाह्य व्योम of_pdt_build_devicetree(phandle root_node, काष्ठा of_pdt_ops *ops);

#पूर्ण_अगर /* _LINUX_OF_PDT_H */
