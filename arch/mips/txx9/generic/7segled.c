<शैली गुरु>
/*
 * 7 Segment LED routines
 * Based on RBTX49xx patch from CELF patch archive.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * (C) Copyright TOSHIBA CORPORATION 2005-2007
 * All Rights Reserved.
 */
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/map_to_7segment.h>
#समावेश <यंत्र/txx9/generic.h>

अटल अचिन्हित पूर्णांक tx_7segled_num;
अटल व्योम (*tx_7segled_अ_दो)(अचिन्हित पूर्णांक pos, अचिन्हित अक्षर val);

व्योम __init txx9_7segled_init(अचिन्हित पूर्णांक num,
			      व्योम (*अ_दो)(अचिन्हित पूर्णांक pos, अचिन्हित अक्षर val))
अणु
	tx_7segled_num = num;
	tx_7segled_अ_दो = अ_दो;
पूर्ण

अटल SEG7_CONVERSION_MAP(txx9_seg7map, MAP_ASCII7SEG_ALPHANUM_LC);

पूर्णांक txx9_7segled_अ_दो(अचिन्हित पूर्णांक pos, अक्षर c)
अणु
	अगर (pos >= tx_7segled_num)
		वापस -EINVAL;
	c = map_to_seg7(&txx9_seg7map, c);
	अगर (c < 0)
		वापस c;
	tx_7segled_अ_दो(pos, c);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार ascii_store(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	अचिन्हित पूर्णांक ch = dev->id;
	txx9_7segled_अ_दो(ch, buf[0]);
	वापस size;
पूर्ण

अटल sमाप_प्रकार raw_store(काष्ठा device *dev,
			 काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	अचिन्हित पूर्णांक ch = dev->id;
	tx_7segled_अ_दो(ch, buf[0]);
	वापस size;
पूर्ण

अटल DEVICE_ATTR_WO(ascii);
अटल DEVICE_ATTR_WO(raw);

अटल sमाप_प्रकार map_seg7_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	स_नकल(buf, &txx9_seg7map, माप(txx9_seg7map));
	वापस माप(txx9_seg7map);
पूर्ण

अटल sमाप_प्रकार map_seg7_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	अगर (size != माप(txx9_seg7map))
		वापस -EINVAL;
	स_नकल(&txx9_seg7map, buf, size);
	वापस size;
पूर्ण

अटल DEVICE_ATTR(map_seg7, 0600, map_seg7_show, map_seg7_store);

अटल काष्ठा bus_type tx_7segled_subsys = अणु
	.name		= "7segled",
	.dev_name	= "7segled",
पूर्ण;

अटल व्योम tx_7segled_release(काष्ठा device *dev)
अणु
	kमुक्त(dev);
पूर्ण

अटल पूर्णांक __init tx_7segled_init_sysfs(व्योम)
अणु
	पूर्णांक error, i;
	अगर (!tx_7segled_num)
		वापस -ENODEV;
	error = subsys_प्रणाली_रेजिस्टर(&tx_7segled_subsys, शून्य);
	अगर (error)
		वापस error;
	error = device_create_file(tx_7segled_subsys.dev_root, &dev_attr_map_seg7);
	अगर (error)
		वापस error;
	क्रम (i = 0; i < tx_7segled_num; i++) अणु
		काष्ठा device *dev;
		dev = kzalloc(माप(*dev), GFP_KERNEL);
		अगर (!dev) अणु
			error = -ENODEV;
			अवरोध;
		पूर्ण
		dev->id = i;
		dev->bus = &tx_7segled_subsys;
		dev->release = &tx_7segled_release;
		error = device_रेजिस्टर(dev);
		अगर (error) अणु
			put_device(dev);
			वापस error;
		पूर्ण
		device_create_file(dev, &dev_attr_ascii);
		device_create_file(dev, &dev_attr_raw);
	पूर्ण
	वापस error;
पूर्ण

device_initcall(tx_7segled_init_sysfs);
