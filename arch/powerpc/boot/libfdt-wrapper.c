<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * This file करोes the necessary पूर्णांकerface mapping between the bootwrapper
 * device tree operations and the पूर्णांकerface provided by shared source
 * files flatdevicetree.[ch].
 *
 * Copyright 2007 David Gibson, IBM Corporation.
 */

#समावेश <मानकघोष.स>
#समावेश <मानकपन.स>
#समावेश <page.h>
#समावेश <libfdt.h>
#समावेश "ops.h"

#घोषणा DEBUG	0
#घोषणा BAD_ERROR(err)	(((err) < 0) \
			 && ((err) != -FDT_ERR_NOTFOUND) \
			 && ((err) != -FDT_ERR_EXISTS))

#घोषणा check_err(err) \
	(अणु \
		अगर (BAD_ERROR(err) || ((err < 0) && DEBUG)) \
			म_लिखो("%s():%d  %s\n\r", __func__, __LINE__, \
			       fdt_म_त्रुटि(err)); \
		अगर (BAD_ERROR(err)) \
			निकास(); \
		(err < 0) ? -1 : 0; \
	पूर्ण)

#घोषणा offset_devp(off)	\
	(अणु \
		अचिन्हित दीर्घ _offset = (off); \
		check_err(_offset) ? शून्य : (व्योम *)(_offset+1); \
	पूर्ण)

#घोषणा devp_offset_find(devp)	(((अचिन्हित दीर्घ)(devp))-1)
#घोषणा devp_offset(devp)	(devp ? ((अचिन्हित दीर्घ)(devp))-1 : 0)

अटल व्योम *fdt;
अटल व्योम *buf; /* = शून्य */

#घोषणा EXPAND_GRANULARITY	1024

अटल व्योम expand_buf(पूर्णांक minexpand)
अणु
	पूर्णांक size = fdt_totalsize(fdt);
	पूर्णांक rc;

	size = _ALIGN(size + minexpand, EXPAND_GRANULARITY);
	buf = platक्रमm_ops.पुनः_स्मृति(buf, size);
	अगर (!buf)
		fatal("Couldn't find %d bytes to expand device tree\n\r", size);
	rc = fdt_खोलो_पूर्णांकo(fdt, buf, size);
	अगर (rc != 0)
		fatal("Couldn't expand fdt into new buffer: %s\n\r",
		      fdt_म_त्रुटि(rc));

	fdt = buf;
पूर्ण

अटल व्योम *fdt_wrapper_finddevice(स्थिर अक्षर *path)
अणु
	वापस offset_devp(fdt_path_offset(fdt, path));
पूर्ण

अटल पूर्णांक fdt_wrapper_getprop(स्थिर व्योम *devp, स्थिर अक्षर *name,
			       व्योम *buf, स्थिर पूर्णांक buflen)
अणु
	स्थिर व्योम *p;
	पूर्णांक len;

	p = fdt_getprop(fdt, devp_offset(devp), name, &len);
	अगर (!p)
		वापस check_err(len);
	स_नकल(buf, p, min(len, buflen));
	वापस len;
पूर्ण

अटल पूर्णांक fdt_wrapper_setprop(स्थिर व्योम *devp, स्थिर अक्षर *name,
			       स्थिर व्योम *buf, स्थिर पूर्णांक len)
अणु
	पूर्णांक rc;

	rc = fdt_setprop(fdt, devp_offset(devp), name, buf, len);
	अगर (rc == -FDT_ERR_NOSPACE) अणु
		expand_buf(len + 16);
		rc = fdt_setprop(fdt, devp_offset(devp), name, buf, len);
	पूर्ण

	वापस check_err(rc);
पूर्ण

अटल पूर्णांक fdt_wrapper_del_node(स्थिर व्योम *devp)
अणु
	वापस fdt_del_node(fdt, devp_offset(devp));
पूर्ण

अटल व्योम *fdt_wrapper_get_parent(स्थिर व्योम *devp)
अणु
	वापस offset_devp(fdt_parent_offset(fdt, devp_offset(devp)));
पूर्ण

अटल व्योम *fdt_wrapper_create_node(स्थिर व्योम *devp, स्थिर अक्षर *name)
अणु
	पूर्णांक offset;

	offset = fdt_add_subnode(fdt, devp_offset(devp), name);
	अगर (offset == -FDT_ERR_NOSPACE) अणु
		expand_buf(म_माप(name) + 16);
		offset = fdt_add_subnode(fdt, devp_offset(devp), name);
	पूर्ण

	वापस offset_devp(offset);
पूर्ण

अटल व्योम *fdt_wrapper_find_node_by_prop_value(स्थिर व्योम *prev,
						 स्थिर अक्षर *name,
						 स्थिर अक्षर *val,
						 पूर्णांक len)
अणु
	पूर्णांक offset = fdt_node_offset_by_prop_value(fdt, devp_offset_find(prev),
	                                           name, val, len);
	वापस offset_devp(offset);
पूर्ण

अटल व्योम *fdt_wrapper_find_node_by_compatible(स्थिर व्योम *prev,
						 स्थिर अक्षर *val)
अणु
	पूर्णांक offset = fdt_node_offset_by_compatible(fdt, devp_offset_find(prev),
	                                           val);
	वापस offset_devp(offset);
पूर्ण

अटल अक्षर *fdt_wrapper_get_path(स्थिर व्योम *devp, अक्षर *buf, पूर्णांक len)
अणु
	पूर्णांक rc;

	rc = fdt_get_path(fdt, devp_offset(devp), buf, len);
	अगर (check_err(rc))
		वापस शून्य;
	वापस buf;
पूर्ण

अटल अचिन्हित दीर्घ fdt_wrapper_finalize(व्योम)
अणु
	पूर्णांक rc;

	rc = fdt_pack(fdt);
	अगर (rc != 0)
		fatal("Couldn't pack flat tree: %s\n\r",
		      fdt_म_त्रुटि(rc));
	वापस (अचिन्हित दीर्घ)fdt;
पूर्ण

व्योम fdt_init(व्योम *blob)
अणु
	पूर्णांक err;
	पूर्णांक bufsize;

	dt_ops.finddevice = fdt_wrapper_finddevice;
	dt_ops.getprop = fdt_wrapper_getprop;
	dt_ops.setprop = fdt_wrapper_setprop;
	dt_ops.get_parent = fdt_wrapper_get_parent;
	dt_ops.create_node = fdt_wrapper_create_node;
	dt_ops.find_node_by_prop_value = fdt_wrapper_find_node_by_prop_value;
	dt_ops.find_node_by_compatible = fdt_wrapper_find_node_by_compatible;
	dt_ops.del_node = fdt_wrapper_del_node;
	dt_ops.get_path = fdt_wrapper_get_path;
	dt_ops.finalize = fdt_wrapper_finalize;

	/* Make sure the dt blob is the right version and so क्रमth */
	fdt = blob;
	bufsize = fdt_totalsize(fdt) + EXPAND_GRANULARITY;
	buf = दो_स्मृति(bufsize);
	अगर(!buf)
		fatal("malloc failed. can't relocate the device tree\n\r");

	err = fdt_खोलो_पूर्णांकo(fdt, buf, bufsize);

	अगर (err != 0)
		fatal("fdt_init(): %s\n\r", fdt_म_त्रुटि(err));

	fdt = buf;
पूर्ण
