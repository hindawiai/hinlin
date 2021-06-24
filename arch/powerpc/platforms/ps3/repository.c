<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  PS3 repository routines.
 *
 *  Copyright (C) 2006 Sony Computer Entertainment Inc.
 *  Copyright 2006 Sony Corp.
 */

#समावेश <यंत्र/lv1call.h>

#समावेश "platform.h"

क्रमागत ps3_venकरोr_id अणु
	PS3_VENDOR_ID_NONE = 0,
	PS3_VENDOR_ID_SONY = 0x8000000000000000UL,
पूर्ण;

क्रमागत ps3_lpar_id अणु
	PS3_LPAR_ID_CURRENT = 0,
	PS3_LPAR_ID_PME = 1,
पूर्ण;

#घोषणा dump_field(_a, _b) _dump_field(_a, _b, __func__, __LINE__)
अटल व्योम _dump_field(स्थिर अक्षर *hdr, u64 n, स्थिर अक्षर *func, पूर्णांक line)
अणु
#अगर defined(DEBUG)
	अक्षर s[16];
	स्थिर अक्षर *स्थिर in = (स्थिर अक्षर *)&n;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < 8; i++)
		s[i] = (in[i] <= 126 && in[i] >= 32) ? in[i] : '.';
	s[i] = 0;

	pr_devel("%s:%d: %s%016llx : %s\n", func, line, hdr, n, s);
#पूर्ण_अगर
पूर्ण

#घोषणा dump_node_name(_a, _b, _c, _d, _e) \
	_dump_node_name(_a, _b, _c, _d, _e, __func__, __LINE__)
अटल व्योम _dump_node_name(अचिन्हित पूर्णांक lpar_id, u64 n1, u64 n2, u64 n3,
	u64 n4, स्थिर अक्षर *func, पूर्णांक line)
अणु
	pr_devel("%s:%d: lpar: %u\n", func, line, lpar_id);
	_dump_field("n1: ", n1, func, line);
	_dump_field("n2: ", n2, func, line);
	_dump_field("n3: ", n3, func, line);
	_dump_field("n4: ", n4, func, line);
पूर्ण

#घोषणा dump_node(_a, _b, _c, _d, _e, _f, _g) \
	_dump_node(_a, _b, _c, _d, _e, _f, _g, __func__, __LINE__)
अटल व्योम _dump_node(अचिन्हित पूर्णांक lpar_id, u64 n1, u64 n2, u64 n3, u64 n4,
	u64 v1, u64 v2, स्थिर अक्षर *func, पूर्णांक line)
अणु
	pr_devel("%s:%d: lpar: %u\n", func, line, lpar_id);
	_dump_field("n1: ", n1, func, line);
	_dump_field("n2: ", n2, func, line);
	_dump_field("n3: ", n3, func, line);
	_dump_field("n4: ", n4, func, line);
	pr_devel("%s:%d: v1: %016llx\n", func, line, v1);
	pr_devel("%s:%d: v2: %016llx\n", func, line, v2);
पूर्ण

/**
 * make_first_field - Make the first field of a repository node name.
 * @text: Text portion of the field.
 * @index: Numeric index portion of the field.  Use zero क्रम 'don't care'.
 *
 * This routine sets the venकरोr id to zero (non-venकरोr specअगरic).
 * Returns field value.
 */

अटल u64 make_first_field(स्थिर अक्षर *text, u64 index)
अणु
	u64 n;

	म_नकलन((अक्षर *)&n, text, 8);
	वापस PS3_VENDOR_ID_NONE + (n >> 32) + index;
पूर्ण

/**
 * make_field - Make subsequent fields of a repository node name.
 * @text: Text portion of the field.  Use "" क्रम 'don't care'.
 * @index: Numeric index portion of the field.  Use zero क्रम 'don't care'.
 *
 * Returns field value.
 */

अटल u64 make_field(स्थिर अक्षर *text, u64 index)
अणु
	u64 n = 0;

	स_नकल((अक्षर *)&n, text, strnlen(text, माप(n)));
	वापस n + index;
पूर्ण

/**
 * पढ़ो_node - Read a repository node from raw fields.
 * @n1: First field of node name.
 * @n2: Second field of node name.  Use zero क्रम 'don't care'.
 * @n3: Third field of node name.  Use zero क्रम 'don't care'.
 * @n4: Fourth field of node name.  Use zero क्रम 'don't care'.
 * @v1: First repository value (high word).
 * @v2: Second repository value (low word).  Optional parameter, use zero
 *      क्रम 'don't care'.
 */

अटल पूर्णांक पढ़ो_node(अचिन्हित पूर्णांक lpar_id, u64 n1, u64 n2, u64 n3, u64 n4,
	u64 *_v1, u64 *_v2)
अणु
	पूर्णांक result;
	u64 v1;
	u64 v2;

	अगर (lpar_id == PS3_LPAR_ID_CURRENT) अणु
		u64 id;
		lv1_get_logical_partition_id(&id);
		lpar_id = id;
	पूर्ण

	result = lv1_पढ़ो_repository_node(lpar_id, n1, n2, n3, n4, &v1,
		&v2);

	अगर (result) अणु
		pr_warn("%s:%d: lv1_read_repository_node failed: %s\n",
			__func__, __LINE__, ps3_result(result));
		dump_node_name(lpar_id, n1, n2, n3, n4);
		वापस -ENOENT;
	पूर्ण

	dump_node(lpar_id, n1, n2, n3, n4, v1, v2);

	अगर (_v1)
		*_v1 = v1;
	अगर (_v2)
		*_v2 = v2;

	अगर (v1 && !_v1)
		pr_devel("%s:%d: warning: discarding non-zero v1: %016llx\n",
			__func__, __LINE__, v1);
	अगर (v2 && !_v2)
		pr_devel("%s:%d: warning: discarding non-zero v2: %016llx\n",
			__func__, __LINE__, v2);

	वापस 0;
पूर्ण

पूर्णांक ps3_repository_पढ़ो_bus_str(अचिन्हित पूर्णांक bus_index, स्थिर अक्षर *bus_str,
	u64 *value)
अणु
	वापस पढ़ो_node(PS3_LPAR_ID_PME,
		make_first_field("bus", bus_index),
		make_field(bus_str, 0),
		0, 0,
		value, शून्य);
पूर्ण

पूर्णांक ps3_repository_पढ़ो_bus_id(अचिन्हित पूर्णांक bus_index, u64 *bus_id)
अणु
	वापस पढ़ो_node(PS3_LPAR_ID_PME, make_first_field("bus", bus_index),
			 make_field("id", 0), 0, 0, bus_id, शून्य);
पूर्ण

पूर्णांक ps3_repository_पढ़ो_bus_type(अचिन्हित पूर्णांक bus_index,
	क्रमागत ps3_bus_type *bus_type)
अणु
	पूर्णांक result;
	u64 v1 = 0;

	result = पढ़ो_node(PS3_LPAR_ID_PME,
		make_first_field("bus", bus_index),
		make_field("type", 0),
		0, 0,
		&v1, शून्य);
	*bus_type = v1;
	वापस result;
पूर्ण

पूर्णांक ps3_repository_पढ़ो_bus_num_dev(अचिन्हित पूर्णांक bus_index,
	अचिन्हित पूर्णांक *num_dev)
अणु
	पूर्णांक result;
	u64 v1 = 0;

	result = पढ़ो_node(PS3_LPAR_ID_PME,
		make_first_field("bus", bus_index),
		make_field("num_dev", 0),
		0, 0,
		&v1, शून्य);
	*num_dev = v1;
	वापस result;
पूर्ण

पूर्णांक ps3_repository_पढ़ो_dev_str(अचिन्हित पूर्णांक bus_index,
	अचिन्हित पूर्णांक dev_index, स्थिर अक्षर *dev_str, u64 *value)
अणु
	वापस पढ़ो_node(PS3_LPAR_ID_PME,
		make_first_field("bus", bus_index),
		make_field("dev", dev_index),
		make_field(dev_str, 0),
		0,
		value, शून्य);
पूर्ण

पूर्णांक ps3_repository_पढ़ो_dev_id(अचिन्हित पूर्णांक bus_index, अचिन्हित पूर्णांक dev_index,
	u64 *dev_id)
अणु
	वापस पढ़ो_node(PS3_LPAR_ID_PME, make_first_field("bus", bus_index),
			 make_field("dev", dev_index), make_field("id", 0), 0,
			 dev_id, शून्य);
पूर्ण

पूर्णांक ps3_repository_पढ़ो_dev_type(अचिन्हित पूर्णांक bus_index,
	अचिन्हित पूर्णांक dev_index, क्रमागत ps3_dev_type *dev_type)
अणु
	पूर्णांक result;
	u64 v1 = 0;

	result = पढ़ो_node(PS3_LPAR_ID_PME,
		make_first_field("bus", bus_index),
		make_field("dev", dev_index),
		make_field("type", 0),
		0,
		&v1, शून्य);
	*dev_type = v1;
	वापस result;
पूर्ण

पूर्णांक ps3_repository_पढ़ो_dev_पूर्णांकr(अचिन्हित पूर्णांक bus_index,
	अचिन्हित पूर्णांक dev_index, अचिन्हित पूर्णांक पूर्णांकr_index,
	क्रमागत ps3_पूर्णांकerrupt_type *पूर्णांकr_type, अचिन्हित पूर्णांक *पूर्णांकerrupt_id)
अणु
	पूर्णांक result;
	u64 v1 = 0;
	u64 v2 = 0;

	result = पढ़ो_node(PS3_LPAR_ID_PME,
		make_first_field("bus", bus_index),
		make_field("dev", dev_index),
		make_field("intr", पूर्णांकr_index),
		0,
		&v1, &v2);
	*पूर्णांकr_type = v1;
	*पूर्णांकerrupt_id = v2;
	वापस result;
पूर्ण

पूर्णांक ps3_repository_पढ़ो_dev_reg_type(अचिन्हित पूर्णांक bus_index,
	अचिन्हित पूर्णांक dev_index, अचिन्हित पूर्णांक reg_index,
	क्रमागत ps3_reg_type *reg_type)
अणु
	पूर्णांक result;
	u64 v1 = 0;

	result = पढ़ो_node(PS3_LPAR_ID_PME,
		make_first_field("bus", bus_index),
		make_field("dev", dev_index),
		make_field("reg", reg_index),
		make_field("type", 0),
		&v1, शून्य);
	*reg_type = v1;
	वापस result;
पूर्ण

पूर्णांक ps3_repository_पढ़ो_dev_reg_addr(अचिन्हित पूर्णांक bus_index,
	अचिन्हित पूर्णांक dev_index, अचिन्हित पूर्णांक reg_index, u64 *bus_addr, u64 *len)
अणु
	वापस पढ़ो_node(PS3_LPAR_ID_PME,
		make_first_field("bus", bus_index),
		make_field("dev", dev_index),
		make_field("reg", reg_index),
		make_field("data", 0),
		bus_addr, len);
पूर्ण

पूर्णांक ps3_repository_पढ़ो_dev_reg(अचिन्हित पूर्णांक bus_index,
	अचिन्हित पूर्णांक dev_index, अचिन्हित पूर्णांक reg_index,
	क्रमागत ps3_reg_type *reg_type, u64 *bus_addr, u64 *len)
अणु
	पूर्णांक result = ps3_repository_पढ़ो_dev_reg_type(bus_index, dev_index,
		reg_index, reg_type);
	वापस result ? result
		: ps3_repository_पढ़ो_dev_reg_addr(bus_index, dev_index,
		reg_index, bus_addr, len);
पूर्ण



पूर्णांक ps3_repository_find_device(काष्ठा ps3_repository_device *repo)
अणु
	पूर्णांक result;
	काष्ठा ps3_repository_device पंचांगp = *repo;
	अचिन्हित पूर्णांक num_dev;

	BUG_ON(repo->bus_index > 10);
	BUG_ON(repo->dev_index > 10);

	result = ps3_repository_पढ़ो_bus_num_dev(पंचांगp.bus_index, &num_dev);

	अगर (result) अणु
		pr_devel("%s:%d read_bus_num_dev failed\n", __func__, __LINE__);
		वापस result;
	पूर्ण

	pr_devel("%s:%d: bus_type %u, bus_index %u, bus_id %llu, num_dev %u\n",
		__func__, __LINE__, पंचांगp.bus_type, पंचांगp.bus_index, पंचांगp.bus_id,
		num_dev);

	अगर (पंचांगp.dev_index >= num_dev) अणु
		pr_devel("%s:%d: no device found\n", __func__, __LINE__);
		वापस -ENODEV;
	पूर्ण

	result = ps3_repository_पढ़ो_dev_type(पंचांगp.bus_index, पंचांगp.dev_index,
		&पंचांगp.dev_type);

	अगर (result) अणु
		pr_devel("%s:%d read_dev_type failed\n", __func__, __LINE__);
		वापस result;
	पूर्ण

	result = ps3_repository_पढ़ो_dev_id(पंचांगp.bus_index, पंचांगp.dev_index,
		&पंचांगp.dev_id);

	अगर (result) अणु
		pr_devel("%s:%d ps3_repository_read_dev_id failed\n", __func__,
		__LINE__);
		वापस result;
	पूर्ण

	pr_devel("%s:%d: found: dev_type %u, dev_index %u, dev_id %llu\n",
		__func__, __LINE__, पंचांगp.dev_type, पंचांगp.dev_index, पंचांगp.dev_id);

	*repo = पंचांगp;
	वापस 0;
पूर्ण

पूर्णांक ps3_repository_find_device_by_id(काष्ठा ps3_repository_device *repo,
				     u64 bus_id, u64 dev_id)
अणु
	पूर्णांक result = -ENODEV;
	काष्ठा ps3_repository_device पंचांगp;
	अचिन्हित पूर्णांक num_dev;

	pr_devel(" -> %s:%u: find device by id %llu:%llu\n", __func__, __LINE__,
		 bus_id, dev_id);

	क्रम (पंचांगp.bus_index = 0; पंचांगp.bus_index < 10; पंचांगp.bus_index++) अणु
		result = ps3_repository_पढ़ो_bus_id(पंचांगp.bus_index,
						    &पंचांगp.bus_id);
		अगर (result) अणु
			pr_devel("%s:%u read_bus_id(%u) failed\n", __func__,
				 __LINE__, पंचांगp.bus_index);
			वापस result;
		पूर्ण

		अगर (पंचांगp.bus_id == bus_id)
			जाओ found_bus;

		pr_devel("%s:%u: skip, bus_id %llu\n", __func__, __LINE__,
			 पंचांगp.bus_id);
	पूर्ण
	pr_devel(" <- %s:%u: bus not found\n", __func__, __LINE__);
	वापस result;

found_bus:
	result = ps3_repository_पढ़ो_bus_type(पंचांगp.bus_index, &पंचांगp.bus_type);
	अगर (result) अणु
		pr_devel("%s:%u read_bus_type(%u) failed\n", __func__,
			 __LINE__, पंचांगp.bus_index);
		वापस result;
	पूर्ण

	result = ps3_repository_पढ़ो_bus_num_dev(पंचांगp.bus_index, &num_dev);
	अगर (result) अणु
		pr_devel("%s:%u read_bus_num_dev failed\n", __func__,
			 __LINE__);
		वापस result;
	पूर्ण

	क्रम (पंचांगp.dev_index = 0; पंचांगp.dev_index < num_dev; पंचांगp.dev_index++) अणु
		result = ps3_repository_पढ़ो_dev_id(पंचांगp.bus_index,
						    पंचांगp.dev_index,
						    &पंचांगp.dev_id);
		अगर (result) अणु
			pr_devel("%s:%u read_dev_id(%u:%u) failed\n", __func__,
				 __LINE__, पंचांगp.bus_index, पंचांगp.dev_index);
			वापस result;
		पूर्ण

		अगर (पंचांगp.dev_id == dev_id)
			जाओ found_dev;

		pr_devel("%s:%u: skip, dev_id %llu\n", __func__, __LINE__,
			 पंचांगp.dev_id);
	पूर्ण
	pr_devel(" <- %s:%u: dev not found\n", __func__, __LINE__);
	वापस result;

found_dev:
	result = ps3_repository_पढ़ो_dev_type(पंचांगp.bus_index, पंचांगp.dev_index,
					      &पंचांगp.dev_type);
	अगर (result) अणु
		pr_devel("%s:%u read_dev_type failed\n", __func__, __LINE__);
		वापस result;
	पूर्ण

	pr_devel(" <- %s:%u: found: type (%u:%u) index (%u:%u) id (%llu:%llu)\n",
		 __func__, __LINE__, पंचांगp.bus_type, पंचांगp.dev_type, पंचांगp.bus_index,
		 पंचांगp.dev_index, पंचांगp.bus_id, पंचांगp.dev_id);
	*repo = पंचांगp;
	वापस 0;
पूर्ण

पूर्णांक ps3_repository_find_devices(क्रमागत ps3_bus_type bus_type,
	पूर्णांक (*callback)(स्थिर काष्ठा ps3_repository_device *repo))
अणु
	पूर्णांक result = 0;
	काष्ठा ps3_repository_device repo;

	pr_devel(" -> %s:%d: find bus_type %u\n", __func__, __LINE__, bus_type);

	repo.bus_type = bus_type;
	result = ps3_repository_find_bus(repo.bus_type, 0, &repo.bus_index);
	अगर (result) अणु
		pr_devel(" <- %s:%u: bus not found\n", __func__, __LINE__);
		वापस result;
	पूर्ण

	result = ps3_repository_पढ़ो_bus_id(repo.bus_index, &repo.bus_id);
	अगर (result) अणु
		pr_devel("%s:%d read_bus_id(%u) failed\n", __func__, __LINE__,
			 repo.bus_index);
		वापस result;
	पूर्ण

	क्रम (repo.dev_index = 0; ; repo.dev_index++) अणु
		result = ps3_repository_find_device(&repo);
		अगर (result == -ENODEV) अणु
			result = 0;
			अवरोध;
		पूर्ण अन्यथा अगर (result)
			अवरोध;

		result = callback(&repo);
		अगर (result) अणु
			pr_devel("%s:%d: abort at callback\n", __func__,
				__LINE__);
			अवरोध;
		पूर्ण
	पूर्ण

	pr_devel(" <- %s:%d\n", __func__, __LINE__);
	वापस result;
पूर्ण

पूर्णांक ps3_repository_find_bus(क्रमागत ps3_bus_type bus_type, अचिन्हित पूर्णांक from,
	अचिन्हित पूर्णांक *bus_index)
अणु
	अचिन्हित पूर्णांक i;
	क्रमागत ps3_bus_type type;
	पूर्णांक error;

	क्रम (i = from; i < 10; i++) अणु
		error = ps3_repository_पढ़ो_bus_type(i, &type);
		अगर (error) अणु
			pr_devel("%s:%d read_bus_type failed\n",
				__func__, __LINE__);
			*bus_index = अच_पूर्णांक_उच्च;
			वापस error;
		पूर्ण
		अगर (type == bus_type) अणु
			*bus_index = i;
			वापस 0;
		पूर्ण
	पूर्ण
	*bus_index = अच_पूर्णांक_उच्च;
	वापस -ENODEV;
पूर्ण

पूर्णांक ps3_repository_find_पूर्णांकerrupt(स्थिर काष्ठा ps3_repository_device *repo,
	क्रमागत ps3_पूर्णांकerrupt_type पूर्णांकr_type, अचिन्हित पूर्णांक *पूर्णांकerrupt_id)
अणु
	पूर्णांक result = 0;
	अचिन्हित पूर्णांक res_index;

	pr_devel("%s:%d: find intr_type %u\n", __func__, __LINE__, पूर्णांकr_type);

	*पूर्णांकerrupt_id = अच_पूर्णांक_उच्च;

	क्रम (res_index = 0; res_index < 10; res_index++) अणु
		क्रमागत ps3_पूर्णांकerrupt_type t;
		अचिन्हित पूर्णांक id;

		result = ps3_repository_पढ़ो_dev_पूर्णांकr(repo->bus_index,
			repo->dev_index, res_index, &t, &id);

		अगर (result) अणु
			pr_devel("%s:%d read_dev_intr failed\n",
				__func__, __LINE__);
			वापस result;
		पूर्ण

		अगर (t == पूर्णांकr_type) अणु
			*पूर्णांकerrupt_id = id;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (res_index == 10)
		वापस -ENODEV;

	pr_devel("%s:%d: found intr_type %u at res_index %u\n",
		__func__, __LINE__, पूर्णांकr_type, res_index);

	वापस result;
पूर्ण

पूर्णांक ps3_repository_find_reg(स्थिर काष्ठा ps3_repository_device *repo,
	क्रमागत ps3_reg_type reg_type, u64 *bus_addr, u64 *len)
अणु
	पूर्णांक result = 0;
	अचिन्हित पूर्णांक res_index;

	pr_devel("%s:%d: find reg_type %u\n", __func__, __LINE__, reg_type);

	*bus_addr = *len = 0;

	क्रम (res_index = 0; res_index < 10; res_index++) अणु
		क्रमागत ps3_reg_type t;
		u64 a;
		u64 l;

		result = ps3_repository_पढ़ो_dev_reg(repo->bus_index,
			repo->dev_index, res_index, &t, &a, &l);

		अगर (result) अणु
			pr_devel("%s:%d read_dev_reg failed\n",
				__func__, __LINE__);
			वापस result;
		पूर्ण

		अगर (t == reg_type) अणु
			*bus_addr = a;
			*len = l;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (res_index == 10)
		वापस -ENODEV;

	pr_devel("%s:%d: found reg_type %u at res_index %u\n",
		__func__, __LINE__, reg_type, res_index);

	वापस result;
पूर्ण

पूर्णांक ps3_repository_पढ़ो_stor_dev_port(अचिन्हित पूर्णांक bus_index,
	अचिन्हित पूर्णांक dev_index, u64 *port)
अणु
	वापस पढ़ो_node(PS3_LPAR_ID_PME,
		make_first_field("bus", bus_index),
		make_field("dev", dev_index),
		make_field("port", 0),
		0, port, शून्य);
पूर्ण

पूर्णांक ps3_repository_पढ़ो_stor_dev_blk_size(अचिन्हित पूर्णांक bus_index,
	अचिन्हित पूर्णांक dev_index, u64 *blk_size)
अणु
	वापस पढ़ो_node(PS3_LPAR_ID_PME,
		make_first_field("bus", bus_index),
		make_field("dev", dev_index),
		make_field("blk_size", 0),
		0, blk_size, शून्य);
पूर्ण

पूर्णांक ps3_repository_पढ़ो_stor_dev_num_blocks(अचिन्हित पूर्णांक bus_index,
	अचिन्हित पूर्णांक dev_index, u64 *num_blocks)
अणु
	वापस पढ़ो_node(PS3_LPAR_ID_PME,
		make_first_field("bus", bus_index),
		make_field("dev", dev_index),
		make_field("n_blocks", 0),
		0, num_blocks, शून्य);
पूर्ण

पूर्णांक ps3_repository_पढ़ो_stor_dev_num_regions(अचिन्हित पूर्णांक bus_index,
	अचिन्हित पूर्णांक dev_index, अचिन्हित पूर्णांक *num_regions)
अणु
	पूर्णांक result;
	u64 v1 = 0;

	result = पढ़ो_node(PS3_LPAR_ID_PME,
		make_first_field("bus", bus_index),
		make_field("dev", dev_index),
		make_field("n_regs", 0),
		0, &v1, शून्य);
	*num_regions = v1;
	वापस result;
पूर्ण

पूर्णांक ps3_repository_पढ़ो_stor_dev_region_id(अचिन्हित पूर्णांक bus_index,
	अचिन्हित पूर्णांक dev_index, अचिन्हित पूर्णांक region_index,
	अचिन्हित पूर्णांक *region_id)
अणु
	पूर्णांक result;
	u64 v1 = 0;

	result = पढ़ो_node(PS3_LPAR_ID_PME,
	    make_first_field("bus", bus_index),
	    make_field("dev", dev_index),
	    make_field("region", region_index),
	    make_field("id", 0),
	    &v1, शून्य);
	*region_id = v1;
	वापस result;
पूर्ण

पूर्णांक ps3_repository_पढ़ो_stor_dev_region_size(अचिन्हित पूर्णांक bus_index,
	अचिन्हित पूर्णांक dev_index,	अचिन्हित पूर्णांक region_index, u64 *region_size)
अणु
	वापस पढ़ो_node(PS3_LPAR_ID_PME,
	    make_first_field("bus", bus_index),
	    make_field("dev", dev_index),
	    make_field("region", region_index),
	    make_field("size", 0),
	    region_size, शून्य);
पूर्ण

पूर्णांक ps3_repository_पढ़ो_stor_dev_region_start(अचिन्हित पूर्णांक bus_index,
	अचिन्हित पूर्णांक dev_index, अचिन्हित पूर्णांक region_index, u64 *region_start)
अणु
	वापस पढ़ो_node(PS3_LPAR_ID_PME,
	    make_first_field("bus", bus_index),
	    make_field("dev", dev_index),
	    make_field("region", region_index),
	    make_field("start", 0),
	    region_start, शून्य);
पूर्ण

पूर्णांक ps3_repository_पढ़ो_stor_dev_info(अचिन्हित पूर्णांक bus_index,
	अचिन्हित पूर्णांक dev_index, u64 *port, u64 *blk_size,
	u64 *num_blocks, अचिन्हित पूर्णांक *num_regions)
अणु
	पूर्णांक result;

	result = ps3_repository_पढ़ो_stor_dev_port(bus_index, dev_index, port);
	अगर (result)
	    वापस result;

	result = ps3_repository_पढ़ो_stor_dev_blk_size(bus_index, dev_index,
		blk_size);
	अगर (result)
	    वापस result;

	result = ps3_repository_पढ़ो_stor_dev_num_blocks(bus_index, dev_index,
		num_blocks);
	अगर (result)
	    वापस result;

	result = ps3_repository_पढ़ो_stor_dev_num_regions(bus_index, dev_index,
		num_regions);
	वापस result;
पूर्ण

पूर्णांक ps3_repository_पढ़ो_stor_dev_region(अचिन्हित पूर्णांक bus_index,
	अचिन्हित पूर्णांक dev_index, अचिन्हित पूर्णांक region_index,
	अचिन्हित पूर्णांक *region_id, u64 *region_start, u64 *region_size)
अणु
	पूर्णांक result;

	result = ps3_repository_पढ़ो_stor_dev_region_id(bus_index, dev_index,
		region_index, region_id);
	अगर (result)
	    वापस result;

	result = ps3_repository_पढ़ो_stor_dev_region_start(bus_index, dev_index,
		region_index, region_start);
	अगर (result)
	    वापस result;

	result = ps3_repository_पढ़ो_stor_dev_region_size(bus_index, dev_index,
		region_index, region_size);
	वापस result;
पूर्ण

/**
 * ps3_repository_पढ़ो_num_pu - Number of logical PU processors क्रम this lpar.
 */

पूर्णांक ps3_repository_पढ़ो_num_pu(u64 *num_pu)
अणु
	*num_pu = 0;
	वापस पढ़ो_node(PS3_LPAR_ID_CURRENT,
			   make_first_field("bi", 0),
			   make_field("pun", 0),
			   0, 0,
			   num_pu, शून्य);
पूर्ण

/**
 * ps3_repository_पढ़ो_pu_id - Read the logical PU id.
 * @pu_index: Zero based index.
 * @pu_id: The logical PU id.
 */

पूर्णांक ps3_repository_पढ़ो_pu_id(अचिन्हित पूर्णांक pu_index, u64 *pu_id)
अणु
	वापस पढ़ो_node(PS3_LPAR_ID_CURRENT,
		make_first_field("bi", 0),
		make_field("pu", pu_index),
		0, 0,
		pu_id, शून्य);
पूर्ण

पूर्णांक ps3_repository_पढ़ो_rm_size(अचिन्हित पूर्णांक ppe_id, u64 *rm_size)
अणु
	वापस पढ़ो_node(PS3_LPAR_ID_CURRENT,
		make_first_field("bi", 0),
		make_field("pu", 0),
		ppe_id,
		make_field("rm_size", 0),
		rm_size, शून्य);
पूर्ण

पूर्णांक ps3_repository_पढ़ो_region_total(u64 *region_total)
अणु
	वापस पढ़ो_node(PS3_LPAR_ID_CURRENT,
		make_first_field("bi", 0),
		make_field("rgntotal", 0),
		0, 0,
		region_total, शून्य);
पूर्ण

/**
 * ps3_repository_पढ़ो_mm_info - Read mm info क्रम single pu प्रणाली.
 * @rm_base: Real mode memory base address.
 * @rm_size: Real mode memory size.
 * @region_total: Maximum memory region size.
 */

पूर्णांक ps3_repository_पढ़ो_mm_info(u64 *rm_base, u64 *rm_size, u64 *region_total)
अणु
	पूर्णांक result;
	u64 ppe_id;

	lv1_get_logical_ppe_id(&ppe_id);
	*rm_base = 0;
	result = ps3_repository_पढ़ो_rm_size(ppe_id, rm_size);
	वापस result ? result
		: ps3_repository_पढ़ो_region_total(region_total);
पूर्ण

/**
 * ps3_repository_पढ़ो_highmem_region_count - Read the number of highmem regions
 *
 * Bootloaders must arrange the repository nodes such that regions are indexed
 * with a region_index from 0 to region_count-1.
 */

पूर्णांक ps3_repository_पढ़ो_highmem_region_count(अचिन्हित पूर्णांक *region_count)
अणु
	पूर्णांक result;
	u64 v1 = 0;

	result = पढ़ो_node(PS3_LPAR_ID_CURRENT,
		make_first_field("highmem", 0),
		make_field("region", 0),
		make_field("count", 0),
		0,
		&v1, शून्य);
	*region_count = v1;
	वापस result;
पूर्ण


पूर्णांक ps3_repository_पढ़ो_highmem_base(अचिन्हित पूर्णांक region_index,
	u64 *highmem_base)
अणु
	वापस पढ़ो_node(PS3_LPAR_ID_CURRENT,
		make_first_field("highmem", 0),
		make_field("region", region_index),
		make_field("base", 0),
		0,
		highmem_base, शून्य);
पूर्ण

पूर्णांक ps3_repository_पढ़ो_highmem_size(अचिन्हित पूर्णांक region_index,
	u64 *highmem_size)
अणु
	वापस पढ़ो_node(PS3_LPAR_ID_CURRENT,
		make_first_field("highmem", 0),
		make_field("region", region_index),
		make_field("size", 0),
		0,
		highmem_size, शून्य);
पूर्ण

/**
 * ps3_repository_पढ़ो_highmem_info - Read high memory region info
 * @region_index: Region index, अणु0,..,region_count-1पूर्ण.
 * @highmem_base: High memory base address.
 * @highmem_size: High memory size.
 *
 * Bootloaders that pपुनः_स्मृतिate highmem regions must place the
 * region info पूर्णांकo the repository at these well known nodes.
 */

पूर्णांक ps3_repository_पढ़ो_highmem_info(अचिन्हित पूर्णांक region_index,
	u64 *highmem_base, u64 *highmem_size)
अणु
	पूर्णांक result;

	*highmem_base = 0;
	result = ps3_repository_पढ़ो_highmem_base(region_index, highmem_base);
	वापस result ? result
		: ps3_repository_पढ़ो_highmem_size(region_index, highmem_size);
पूर्ण

/**
 * ps3_repository_पढ़ो_num_spu_reserved - Number of physical spus reserved.
 * @num_spu: Number of physical spus.
 */

पूर्णांक ps3_repository_पढ़ो_num_spu_reserved(अचिन्हित पूर्णांक *num_spu_reserved)
अणु
	पूर्णांक result;
	u64 v1 = 0;

	result = पढ़ो_node(PS3_LPAR_ID_CURRENT,
		make_first_field("bi", 0),
		make_field("spun", 0),
		0, 0,
		&v1, शून्य);
	*num_spu_reserved = v1;
	वापस result;
पूर्ण

/**
 * ps3_repository_पढ़ो_num_spu_resource_id - Number of spu resource reservations.
 * @num_resource_id: Number of spu resource ids.
 */

पूर्णांक ps3_repository_पढ़ो_num_spu_resource_id(अचिन्हित पूर्णांक *num_resource_id)
अणु
	पूर्णांक result;
	u64 v1 = 0;

	result = पढ़ो_node(PS3_LPAR_ID_CURRENT,
		make_first_field("bi", 0),
		make_field("spursvn", 0),
		0, 0,
		&v1, शून्य);
	*num_resource_id = v1;
	वापस result;
पूर्ण

/**
 * ps3_repository_पढ़ो_spu_resource_id - spu resource reservation id value.
 * @res_index: Resource reservation index.
 * @resource_type: Resource reservation type.
 * @resource_id: Resource reservation id.
 */

पूर्णांक ps3_repository_पढ़ो_spu_resource_id(अचिन्हित पूर्णांक res_index,
	क्रमागत ps3_spu_resource_type *resource_type, अचिन्हित पूर्णांक *resource_id)
अणु
	पूर्णांक result;
	u64 v1 = 0;
	u64 v2 = 0;

	result = पढ़ो_node(PS3_LPAR_ID_CURRENT,
		make_first_field("bi", 0),
		make_field("spursv", 0),
		res_index,
		0,
		&v1, &v2);
	*resource_type = v1;
	*resource_id = v2;
	वापस result;
पूर्ण

अटल पूर्णांक ps3_repository_पढ़ो_boot_dat_address(u64 *address)
अणु
	वापस पढ़ो_node(PS3_LPAR_ID_CURRENT,
		make_first_field("bi", 0),
		make_field("boot_dat", 0),
		make_field("address", 0),
		0,
		address, शून्य);
पूर्ण

पूर्णांक ps3_repository_पढ़ो_boot_dat_size(अचिन्हित पूर्णांक *size)
अणु
	पूर्णांक result;
	u64 v1 = 0;

	result = पढ़ो_node(PS3_LPAR_ID_CURRENT,
		make_first_field("bi", 0),
		make_field("boot_dat", 0),
		make_field("size", 0),
		0,
		&v1, शून्य);
	*size = v1;
	वापस result;
पूर्ण

पूर्णांक ps3_repository_पढ़ो_vuart_av_port(अचिन्हित पूर्णांक *port)
अणु
	पूर्णांक result;
	u64 v1 = 0;

	result = पढ़ो_node(PS3_LPAR_ID_CURRENT,
		make_first_field("bi", 0),
		make_field("vir_uart", 0),
		make_field("port", 0),
		make_field("avset", 0),
		&v1, शून्य);
	*port = v1;
	वापस result;
पूर्ण

पूर्णांक ps3_repository_पढ़ो_vuart_sysmgr_port(अचिन्हित पूर्णांक *port)
अणु
	पूर्णांक result;
	u64 v1 = 0;

	result = पढ़ो_node(PS3_LPAR_ID_CURRENT,
		make_first_field("bi", 0),
		make_field("vir_uart", 0),
		make_field("port", 0),
		make_field("sysmgr", 0),
		&v1, शून्य);
	*port = v1;
	वापस result;
पूर्ण

/**
  * ps3_repository_पढ़ो_boot_dat_info - Get address and size of cell_ext_os_area.
  * address: lpar address of cell_ext_os_area
  * @size: size of cell_ext_os_area
  */

पूर्णांक ps3_repository_पढ़ो_boot_dat_info(u64 *lpar_addr, अचिन्हित पूर्णांक *size)
अणु
	पूर्णांक result;

	*size = 0;
	result = ps3_repository_पढ़ो_boot_dat_address(lpar_addr);
	वापस result ? result
		: ps3_repository_पढ़ो_boot_dat_size(size);
पूर्ण

/**
 * ps3_repository_पढ़ो_num_be - Number of physical BE processors in the प्रणाली.
 */

पूर्णांक ps3_repository_पढ़ो_num_be(अचिन्हित पूर्णांक *num_be)
अणु
	पूर्णांक result;
	u64 v1 = 0;

	result = पढ़ो_node(PS3_LPAR_ID_PME,
		make_first_field("ben", 0),
		0,
		0,
		0,
		&v1, शून्य);
	*num_be = v1;
	वापस result;
पूर्ण

/**
 * ps3_repository_पढ़ो_be_node_id - Read the physical BE processor node id.
 * @be_index: Zero based index.
 * @node_id: The BE processor node id.
 */

पूर्णांक ps3_repository_पढ़ो_be_node_id(अचिन्हित पूर्णांक be_index, u64 *node_id)
अणु
	वापस पढ़ो_node(PS3_LPAR_ID_PME,
		make_first_field("be", be_index),
		0,
		0,
		0,
		node_id, शून्य);
पूर्ण

/**
 * ps3_repository_पढ़ो_be_id - Read the physical BE processor id.
 * @node_id: The BE processor node id.
 * @be_id: The BE processor id.
 */

पूर्णांक ps3_repository_पढ़ो_be_id(u64 node_id, u64 *be_id)
अणु
	वापस पढ़ो_node(PS3_LPAR_ID_PME,
		make_first_field("be", 0),
		node_id,
		0,
		0,
		be_id, शून्य);
पूर्ण

पूर्णांक ps3_repository_पढ़ो_tb_freq(u64 node_id, u64 *tb_freq)
अणु
	वापस पढ़ो_node(PS3_LPAR_ID_PME,
		make_first_field("be", 0),
		node_id,
		make_field("clock", 0),
		0,
		tb_freq, शून्य);
पूर्ण

पूर्णांक ps3_repository_पढ़ो_be_tb_freq(अचिन्हित पूर्णांक be_index, u64 *tb_freq)
अणु
	पूर्णांक result;
	u64 node_id;

	*tb_freq = 0;
	result = ps3_repository_पढ़ो_be_node_id(be_index, &node_id);
	वापस result ? result
		: ps3_repository_पढ़ो_tb_freq(node_id, tb_freq);
पूर्ण

पूर्णांक ps3_repository_पढ़ो_lpm_privileges(अचिन्हित पूर्णांक be_index, u64 *lpar,
	u64 *rights)
अणु
	पूर्णांक result;
	u64 node_id;

	*lpar = 0;
	*rights = 0;
	result = ps3_repository_पढ़ो_be_node_id(be_index, &node_id);
	वापस result ? result
		: पढ़ो_node(PS3_LPAR_ID_PME,
			    make_first_field("be", 0),
			    node_id,
			    make_field("lpm", 0),
			    make_field("priv", 0),
			    lpar, rights);
पूर्ण

#अगर defined(CONFIG_PS3_REPOSITORY_WRITE)

अटल पूर्णांक create_node(u64 n1, u64 n2, u64 n3, u64 n4, u64 v1, u64 v2)
अणु
	पूर्णांक result;

	dump_node(0, n1, n2, n3, n4, v1, v2);

	result = lv1_create_repository_node(n1, n2, n3, n4, v1, v2);

	अगर (result) अणु
		pr_devel("%s:%d: lv1_create_repository_node failed: %s\n",
			__func__, __LINE__, ps3_result(result));
		वापस -ENOENT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक delete_node(u64 n1, u64 n2, u64 n3, u64 n4)
अणु
	पूर्णांक result;

	dump_node(0, n1, n2, n3, n4, 0, 0);

	result = lv1_delete_repository_node(n1, n2, n3, n4);

	अगर (result) अणु
		pr_devel("%s:%d: lv1_delete_repository_node failed: %s\n",
			__func__, __LINE__, ps3_result(result));
		वापस -ENOENT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ग_लिखो_node(u64 n1, u64 n2, u64 n3, u64 n4, u64 v1, u64 v2)
अणु
	पूर्णांक result;

	result = create_node(n1, n2, n3, n4, v1, v2);

	अगर (!result)
		वापस 0;

	result = lv1_ग_लिखो_repository_node(n1, n2, n3, n4, v1, v2);

	अगर (result) अणु
		pr_devel("%s:%d: lv1_write_repository_node failed: %s\n",
			__func__, __LINE__, ps3_result(result));
		वापस -ENOENT;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ps3_repository_ग_लिखो_highmem_region_count(अचिन्हित पूर्णांक region_count)
अणु
	पूर्णांक result;
	u64 v1 = (u64)region_count;

	result = ग_लिखो_node(
		make_first_field("highmem", 0),
		make_field("region", 0),
		make_field("count", 0),
		0,
		v1, 0);
	वापस result;
पूर्ण

पूर्णांक ps3_repository_ग_लिखो_highmem_base(अचिन्हित पूर्णांक region_index,
	u64 highmem_base)
अणु
	वापस ग_लिखो_node(
		make_first_field("highmem", 0),
		make_field("region", region_index),
		make_field("base", 0),
		0,
		highmem_base, 0);
पूर्ण

पूर्णांक ps3_repository_ग_लिखो_highmem_size(अचिन्हित पूर्णांक region_index,
	u64 highmem_size)
अणु
	वापस ग_लिखो_node(
		make_first_field("highmem", 0),
		make_field("region", region_index),
		make_field("size", 0),
		0,
		highmem_size, 0);
पूर्ण

पूर्णांक ps3_repository_ग_लिखो_highmem_info(अचिन्हित पूर्णांक region_index,
	u64 highmem_base, u64 highmem_size)
अणु
	पूर्णांक result;

	result = ps3_repository_ग_लिखो_highmem_base(region_index, highmem_base);
	वापस result ? result
		: ps3_repository_ग_लिखो_highmem_size(region_index, highmem_size);
पूर्ण

अटल पूर्णांक ps3_repository_delete_highmem_base(अचिन्हित पूर्णांक region_index)
अणु
	वापस delete_node(
		make_first_field("highmem", 0),
		make_field("region", region_index),
		make_field("base", 0),
		0);
पूर्ण

अटल पूर्णांक ps3_repository_delete_highmem_size(अचिन्हित पूर्णांक region_index)
अणु
	वापस delete_node(
		make_first_field("highmem", 0),
		make_field("region", region_index),
		make_field("size", 0),
		0);
पूर्ण

पूर्णांक ps3_repository_delete_highmem_info(अचिन्हित पूर्णांक region_index)
अणु
	पूर्णांक result;

	result = ps3_repository_delete_highmem_base(region_index);
	result += ps3_repository_delete_highmem_size(region_index);

	वापस result ? -1 : 0;
पूर्ण

#पूर्ण_अगर /* defined(CONFIG_PS3_REPOSITORY_WRITE) */

#अगर defined(DEBUG)

पूर्णांक ps3_repository_dump_resource_info(स्थिर काष्ठा ps3_repository_device *repo)
अणु
	पूर्णांक result = 0;
	अचिन्हित पूर्णांक res_index;

	pr_devel(" -> %s:%d: (%u:%u)\n", __func__, __LINE__,
		repo->bus_index, repo->dev_index);

	क्रम (res_index = 0; res_index < 10; res_index++) अणु
		क्रमागत ps3_पूर्णांकerrupt_type पूर्णांकr_type;
		अचिन्हित पूर्णांक पूर्णांकerrupt_id;

		result = ps3_repository_पढ़ो_dev_पूर्णांकr(repo->bus_index,
			repo->dev_index, res_index, &पूर्णांकr_type, &पूर्णांकerrupt_id);

		अगर (result) अणु
			अगर (result !=  LV1_NO_ENTRY)
				pr_devel("%s:%d ps3_repository_read_dev_intr"
					" (%u:%u) failed\n", __func__, __LINE__,
					repo->bus_index, repo->dev_index);
			अवरोध;
		पूर्ण

		pr_devel("%s:%d (%u:%u) intr_type %u, interrupt_id %u\n",
			__func__, __LINE__, repo->bus_index, repo->dev_index,
			पूर्णांकr_type, पूर्णांकerrupt_id);
	पूर्ण

	क्रम (res_index = 0; res_index < 10; res_index++) अणु
		क्रमागत ps3_reg_type reg_type;
		u64 bus_addr;
		u64 len;

		result = ps3_repository_पढ़ो_dev_reg(repo->bus_index,
			repo->dev_index, res_index, &reg_type, &bus_addr, &len);

		अगर (result) अणु
			अगर (result !=  LV1_NO_ENTRY)
				pr_devel("%s:%d ps3_repository_read_dev_reg"
					" (%u:%u) failed\n", __func__, __LINE__,
					repo->bus_index, repo->dev_index);
			अवरोध;
		पूर्ण

		pr_devel("%s:%d (%u:%u) reg_type %u, bus_addr %llxh, len %llxh\n",
			__func__, __LINE__, repo->bus_index, repo->dev_index,
			reg_type, bus_addr, len);
	पूर्ण

	pr_devel(" <- %s:%d\n", __func__, __LINE__);
	वापस result;
पूर्ण

अटल पूर्णांक dump_stor_dev_info(काष्ठा ps3_repository_device *repo)
अणु
	पूर्णांक result = 0;
	अचिन्हित पूर्णांक num_regions, region_index;
	u64 port, blk_size, num_blocks;

	pr_devel(" -> %s:%d: (%u:%u)\n", __func__, __LINE__,
		repo->bus_index, repo->dev_index);

	result = ps3_repository_पढ़ो_stor_dev_info(repo->bus_index,
		repo->dev_index, &port, &blk_size, &num_blocks, &num_regions);
	अगर (result) अणु
		pr_devel("%s:%d ps3_repository_read_stor_dev_info"
			" (%u:%u) failed\n", __func__, __LINE__,
			repo->bus_index, repo->dev_index);
		जाओ out;
	पूर्ण

	pr_devel("%s:%d  (%u:%u): port %llu, blk_size %llu, num_blocks "
		 "%llu, num_regions %u\n",
		 __func__, __LINE__, repo->bus_index, repo->dev_index,
		port, blk_size, num_blocks, num_regions);

	क्रम (region_index = 0; region_index < num_regions; region_index++) अणु
		अचिन्हित पूर्णांक region_id;
		u64 region_start, region_size;

		result = ps3_repository_पढ़ो_stor_dev_region(repo->bus_index,
			repo->dev_index, region_index, &region_id,
			&region_start, &region_size);
		अगर (result) अणु
			 pr_devel("%s:%d ps3_repository_read_stor_dev_region"
				  " (%u:%u) failed\n", __func__, __LINE__,
				  repo->bus_index, repo->dev_index);
			अवरोध;
		पूर्ण

		pr_devel("%s:%d (%u:%u) region_id %u, start %lxh, size %lxh\n",
			__func__, __LINE__, repo->bus_index, repo->dev_index,
			region_id, (अचिन्हित दीर्घ)region_start,
			(अचिन्हित दीर्घ)region_size);
	पूर्ण

out:
	pr_devel(" <- %s:%d\n", __func__, __LINE__);
	वापस result;
पूर्ण

अटल पूर्णांक dump_device_info(काष्ठा ps3_repository_device *repo,
	अचिन्हित पूर्णांक num_dev)
अणु
	पूर्णांक result = 0;

	pr_devel(" -> %s:%d: bus_%u\n", __func__, __LINE__, repo->bus_index);

	क्रम (repo->dev_index = 0; repo->dev_index < num_dev;
		repo->dev_index++) अणु

		result = ps3_repository_पढ़ो_dev_type(repo->bus_index,
			repo->dev_index, &repo->dev_type);

		अगर (result) अणु
			pr_devel("%s:%d ps3_repository_read_dev_type"
				" (%u:%u) failed\n", __func__, __LINE__,
				repo->bus_index, repo->dev_index);
			अवरोध;
		पूर्ण

		result = ps3_repository_पढ़ो_dev_id(repo->bus_index,
			repo->dev_index, &repo->dev_id);

		अगर (result) अणु
			pr_devel("%s:%d ps3_repository_read_dev_id"
				" (%u:%u) failed\n", __func__, __LINE__,
				repo->bus_index, repo->dev_index);
			जारी;
		पूर्ण

		pr_devel("%s:%d  (%u:%u): dev_type %u, dev_id %lu\n", __func__,
			__LINE__, repo->bus_index, repo->dev_index,
			repo->dev_type, (अचिन्हित दीर्घ)repo->dev_id);

		ps3_repository_dump_resource_info(repo);

		अगर (repo->bus_type == PS3_BUS_TYPE_STORAGE)
			dump_stor_dev_info(repo);
	पूर्ण

	pr_devel(" <- %s:%d\n", __func__, __LINE__);
	वापस result;
पूर्ण

पूर्णांक ps3_repository_dump_bus_info(व्योम)
अणु
	पूर्णांक result = 0;
	काष्ठा ps3_repository_device repo;

	pr_devel(" -> %s:%d\n", __func__, __LINE__);

	स_रखो(&repo, 0, माप(repo));

	क्रम (repo.bus_index = 0; repo.bus_index < 10; repo.bus_index++) अणु
		अचिन्हित पूर्णांक num_dev;

		result = ps3_repository_पढ़ो_bus_type(repo.bus_index,
			&repo.bus_type);

		अगर (result) अणु
			pr_devel("%s:%d read_bus_type(%u) failed\n",
				__func__, __LINE__, repo.bus_index);
			अवरोध;
		पूर्ण

		result = ps3_repository_पढ़ो_bus_id(repo.bus_index,
			&repo.bus_id);

		अगर (result) अणु
			pr_devel("%s:%d read_bus_id(%u) failed\n",
				__func__, __LINE__, repo.bus_index);
			जारी;
		पूर्ण

		अगर (repo.bus_index != repo.bus_id)
			pr_devel("%s:%d bus_index != bus_id\n",
				__func__, __LINE__);

		result = ps3_repository_पढ़ो_bus_num_dev(repo.bus_index,
			&num_dev);

		अगर (result) अणु
			pr_devel("%s:%d read_bus_num_dev(%u) failed\n",
				__func__, __LINE__, repo.bus_index);
			जारी;
		पूर्ण

		pr_devel("%s:%d bus_%u: bus_type %u, bus_id %lu, num_dev %u\n",
			__func__, __LINE__, repo.bus_index, repo.bus_type,
			(अचिन्हित दीर्घ)repo.bus_id, num_dev);

		dump_device_info(&repo, num_dev);
	पूर्ण

	pr_devel(" <- %s:%d\n", __func__, __LINE__);
	वापस result;
पूर्ण

#पूर्ण_अगर /* defined(DEBUG) */
