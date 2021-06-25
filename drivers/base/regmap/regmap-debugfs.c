<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Register map access API - debugfs
//
// Copyright 2011 Wolfson Microelectronics plc
//
// Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>

#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/device.h>
#समावेश <linux/list.h>

#समावेश "internal.h"

काष्ठा regmap_debugfs_node अणु
	काष्ठा regmap *map;
	काष्ठा list_head link;
पूर्ण;

अटल अचिन्हित पूर्णांक dummy_index;
अटल काष्ठा dentry *regmap_debugfs_root;
अटल LIST_HEAD(regmap_debugfs_early_list);
अटल DEFINE_MUTEX(regmap_debugfs_early_lock);

/* Calculate the length of a fixed क्रमmat  */
अटल माप_प्रकार regmap_calc_reg_len(पूर्णांक max_val)
अणु
	वापस snम_लिखो(शून्य, 0, "%x", max_val);
पूर्ण

अटल sमाप_प्रकार regmap_name_पढ़ो_file(काष्ठा file *file,
				     अक्षर __user *user_buf, माप_प्रकार count,
				     loff_t *ppos)
अणु
	काष्ठा regmap *map = file->निजी_data;
	स्थिर अक्षर *name = "nodev";
	पूर्णांक ret;
	अक्षर *buf;

	buf = kदो_स्मृति(PAGE_SIZE, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	अगर (map->dev && map->dev->driver)
		name = map->dev->driver->name;

	ret = snम_लिखो(buf, PAGE_SIZE, "%s\n", name);
	अगर (ret < 0) अणु
		kमुक्त(buf);
		वापस ret;
	पूर्ण

	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, ret);
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations regmap_name_fops = अणु
	.खोलो = simple_खोलो,
	.पढ़ो = regmap_name_पढ़ो_file,
	.llseek = शेष_llseek,
पूर्ण;

अटल व्योम regmap_debugfs_मुक्त_dump_cache(काष्ठा regmap *map)
अणु
	काष्ठा regmap_debugfs_off_cache *c;

	जबतक (!list_empty(&map->debugfs_off_cache)) अणु
		c = list_first_entry(&map->debugfs_off_cache,
				     काष्ठा regmap_debugfs_off_cache,
				     list);
		list_del(&c->list);
		kमुक्त(c);
	पूर्ण
पूर्ण

अटल bool regmap_prपूर्णांकable(काष्ठा regmap *map, अचिन्हित पूर्णांक reg)
अणु
	अगर (regmap_precious(map, reg))
		वापस false;

	अगर (!regmap_पढ़ोable(map, reg) && !regmap_cached(map, reg))
		वापस false;

	वापस true;
पूर्ण

/*
 * Work out where the start offset maps पूर्णांकo रेजिस्टर numbers, bearing
 * in mind that we suppress hidden रेजिस्टरs.
 */
अटल अचिन्हित पूर्णांक regmap_debugfs_get_dump_start(काष्ठा regmap *map,
						  अचिन्हित पूर्णांक base,
						  loff_t from,
						  loff_t *pos)
अणु
	काष्ठा regmap_debugfs_off_cache *c = शून्य;
	loff_t p = 0;
	अचिन्हित पूर्णांक i, ret;
	अचिन्हित पूर्णांक fpos_offset;
	अचिन्हित पूर्णांक reg_offset;

	/* Suppress the cache अगर we're using a subrange */
	अगर (base)
		वापस base;

	/*
	 * If we करोn't have a cache build one so we don't have to करो a
	 * linear scan each समय.
	 */
	mutex_lock(&map->cache_lock);
	i = base;
	अगर (list_empty(&map->debugfs_off_cache)) अणु
		क्रम (; i <= map->max_रेजिस्टर; i += map->reg_stride) अणु
			/* Skip unprपूर्णांकed रेजिस्टरs, closing off cache entry */
			अगर (!regmap_prपूर्णांकable(map, i)) अणु
				अगर (c) अणु
					c->max = p - 1;
					c->max_reg = i - map->reg_stride;
					list_add_tail(&c->list,
						      &map->debugfs_off_cache);
					c = शून्य;
				पूर्ण

				जारी;
			पूर्ण

			/* No cache entry?  Start a new one */
			अगर (!c) अणु
				c = kzalloc(माप(*c), GFP_KERNEL);
				अगर (!c) अणु
					regmap_debugfs_मुक्त_dump_cache(map);
					mutex_unlock(&map->cache_lock);
					वापस base;
				पूर्ण
				c->min = p;
				c->base_reg = i;
			पूर्ण

			p += map->debugfs_tot_len;
		पूर्ण
	पूर्ण

	/* Close the last entry off अगर we didn't scan beyond it */
	अगर (c) अणु
		c->max = p - 1;
		c->max_reg = i - map->reg_stride;
		list_add_tail(&c->list,
			      &map->debugfs_off_cache);
	पूर्ण

	/*
	 * This should never happen; we वापस above अगर we fail to
	 * allocate and we should never be in this code अगर there are
	 * no रेजिस्टरs at all.
	 */
	WARN_ON(list_empty(&map->debugfs_off_cache));
	ret = base;

	/* Find the relevant block:offset */
	list_क्रम_each_entry(c, &map->debugfs_off_cache, list) अणु
		अगर (from >= c->min && from <= c->max) अणु
			fpos_offset = from - c->min;
			reg_offset = fpos_offset / map->debugfs_tot_len;
			*pos = c->min + (reg_offset * map->debugfs_tot_len);
			mutex_unlock(&map->cache_lock);
			वापस c->base_reg + (reg_offset * map->reg_stride);
		पूर्ण

		*pos = c->max;
		ret = c->max_reg;
	पूर्ण
	mutex_unlock(&map->cache_lock);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम regmap_calc_tot_len(काष्ठा regmap *map,
				       व्योम *buf, माप_प्रकार count)
अणु
	/* Calculate the length of a fixed क्रमmat  */
	अगर (!map->debugfs_tot_len) अणु
		map->debugfs_reg_len = regmap_calc_reg_len(map->max_रेजिस्टर);
		map->debugfs_val_len = 2 * map->क्रमmat.val_bytes;
		map->debugfs_tot_len = map->debugfs_reg_len +
			map->debugfs_val_len + 3;      /* : \न */
	पूर्ण
पूर्ण

अटल पूर्णांक regmap_next_पढ़ोable_reg(काष्ठा regmap *map, पूर्णांक reg)
अणु
	काष्ठा regmap_debugfs_off_cache *c;
	पूर्णांक ret = -EINVAL;

	अगर (regmap_prपूर्णांकable(map, reg + map->reg_stride)) अणु
		ret = reg + map->reg_stride;
	पूर्ण अन्यथा अणु
		mutex_lock(&map->cache_lock);
		list_क्रम_each_entry(c, &map->debugfs_off_cache, list) अणु
			अगर (reg > c->max_reg)
				जारी;
			अगर (reg < c->base_reg) अणु
				ret = c->base_reg;
				अवरोध;
			पूर्ण
		पूर्ण
		mutex_unlock(&map->cache_lock);
	पूर्ण
	वापस ret;
पूर्ण

अटल sमाप_प्रकार regmap_पढ़ो_debugfs(काष्ठा regmap *map, अचिन्हित पूर्णांक from,
				   अचिन्हित पूर्णांक to, अक्षर __user *user_buf,
				   माप_प्रकार count, loff_t *ppos)
अणु
	माप_प्रकार buf_pos = 0;
	loff_t p = *ppos;
	sमाप_प्रकार ret;
	पूर्णांक i;
	अक्षर *buf;
	अचिन्हित पूर्णांक val, start_reg;

	अगर (*ppos < 0 || !count)
		वापस -EINVAL;

	अगर (count > (PAGE_SIZE << (MAX_ORDER - 1)))
		count = PAGE_SIZE << (MAX_ORDER - 1);

	buf = kदो_स्मृति(count, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	regmap_calc_tot_len(map, buf, count);

	/* Work out which रेजिस्टर we're starting at */
	start_reg = regmap_debugfs_get_dump_start(map, from, *ppos, &p);

	क्रम (i = start_reg; i >= 0 && i <= to;
	     i = regmap_next_पढ़ोable_reg(map, i)) अणु

		/* If we're in the region the user is trying to पढ़ो */
		अगर (p >= *ppos) अणु
			/* ...but not beyond it */
			अगर (buf_pos + map->debugfs_tot_len > count)
				अवरोध;

			/* Format the रेजिस्टर */
			snम_लिखो(buf + buf_pos, count - buf_pos, "%.*x: ",
				 map->debugfs_reg_len, i - from);
			buf_pos += map->debugfs_reg_len + 2;

			/* Format the value, ग_लिखो all X अगर we can't पढ़ो */
			ret = regmap_पढ़ो(map, i, &val);
			अगर (ret == 0)
				snम_लिखो(buf + buf_pos, count - buf_pos,
					 "%.*x", map->debugfs_val_len, val);
			अन्यथा
				स_रखो(buf + buf_pos, 'X',
				       map->debugfs_val_len);
			buf_pos += 2 * map->क्रमmat.val_bytes;

			buf[buf_pos++] = '\n';
		पूर्ण
		p += map->debugfs_tot_len;
	पूर्ण

	ret = buf_pos;

	अगर (copy_to_user(user_buf, buf, buf_pos)) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण

	*ppos += buf_pos;

out:
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार regmap_map_पढ़ो_file(काष्ठा file *file, अक्षर __user *user_buf,
				    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा regmap *map = file->निजी_data;

	वापस regmap_पढ़ो_debugfs(map, 0, map->max_रेजिस्टर, user_buf,
				   count, ppos);
पूर्ण

#अघोषित REGMAP_ALLOW_WRITE_DEBUGFS
#अगर_घोषित REGMAP_ALLOW_WRITE_DEBUGFS
/*
 * This can be dangerous especially when we have clients such as
 * PMICs, thereक्रमe करोn't provide any real compile समय configuration option
 * क्रम this feature, people who want to use this will need to modअगरy
 * the source code directly.
 */
अटल sमाप_प्रकार regmap_map_ग_लिखो_file(काष्ठा file *file,
				     स्थिर अक्षर __user *user_buf,
				     माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर buf[32];
	माप_प्रकार buf_size;
	अक्षर *start = buf;
	अचिन्हित दीर्घ reg, value;
	काष्ठा regmap *map = file->निजी_data;
	पूर्णांक ret;

	buf_size = min(count, (माप(buf)-1));
	अगर (copy_from_user(buf, user_buf, buf_size))
		वापस -EFAULT;
	buf[buf_size] = 0;

	जबतक (*start == ' ')
		start++;
	reg = simple_म_से_अदीर्घ(start, &start, 16);
	जबतक (*start == ' ')
		start++;
	अगर (kम_से_अदीर्घ(start, 16, &value))
		वापस -EINVAL;

	/* Userspace has been fiddling around behind the kernel's back */
	add_taपूर्णांक(TAINT_USER, LOCKDEP_STILL_OK);

	ret = regmap_ग_लिखो(map, reg, value);
	अगर (ret < 0)
		वापस ret;
	वापस buf_size;
पूर्ण
#अन्यथा
#घोषणा regmap_map_ग_लिखो_file शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा file_operations regmap_map_fops = अणु
	.खोलो = simple_खोलो,
	.पढ़ो = regmap_map_पढ़ो_file,
	.ग_लिखो = regmap_map_ग_लिखो_file,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार regmap_range_पढ़ो_file(काष्ठा file *file, अक्षर __user *user_buf,
				      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा regmap_range_node *range = file->निजी_data;
	काष्ठा regmap *map = range->map;

	वापस regmap_पढ़ो_debugfs(map, range->range_min, range->range_max,
				   user_buf, count, ppos);
पूर्ण

अटल स्थिर काष्ठा file_operations regmap_range_fops = अणु
	.खोलो = simple_खोलो,
	.पढ़ो = regmap_range_पढ़ो_file,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार regmap_reg_ranges_पढ़ो_file(काष्ठा file *file,
					   अक्षर __user *user_buf, माप_प्रकार count,
					   loff_t *ppos)
अणु
	काष्ठा regmap *map = file->निजी_data;
	काष्ठा regmap_debugfs_off_cache *c;
	loff_t p = 0;
	माप_प्रकार buf_pos = 0;
	अक्षर *buf;
	अक्षर *entry;
	पूर्णांक ret;
	अचिन्हित entry_len;

	अगर (*ppos < 0 || !count)
		वापस -EINVAL;

	अगर (count > (PAGE_SIZE << (MAX_ORDER - 1)))
		count = PAGE_SIZE << (MAX_ORDER - 1);

	buf = kदो_स्मृति(count, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	entry = kदो_स्मृति(PAGE_SIZE, GFP_KERNEL);
	अगर (!entry) अणु
		kमुक्त(buf);
		वापस -ENOMEM;
	पूर्ण

	/* While we are at it, build the रेजिस्टर dump cache
	 * now so the पढ़ो() operation on the `रेजिस्टरs' file
	 * can benefit from using the cache.  We करो not care
	 * about the file position inक्रमmation that is contained
	 * in the cache, just about the actual रेजिस्टर blocks */
	regmap_calc_tot_len(map, buf, count);
	regmap_debugfs_get_dump_start(map, 0, *ppos, &p);

	/* Reset file poपूर्णांकer as the fixed-क्रमmat of the `रेजिस्टरs'
	 * file is not compatible with the `range' file */
	p = 0;
	mutex_lock(&map->cache_lock);
	list_क्रम_each_entry(c, &map->debugfs_off_cache, list) अणु
		entry_len = snम_लिखो(entry, PAGE_SIZE, "%x-%x\n",
				     c->base_reg, c->max_reg);
		अगर (p >= *ppos) अणु
			अगर (buf_pos + entry_len > count)
				अवरोध;
			स_नकल(buf + buf_pos, entry, entry_len);
			buf_pos += entry_len;
		पूर्ण
		p += entry_len;
	पूर्ण
	mutex_unlock(&map->cache_lock);

	kमुक्त(entry);
	ret = buf_pos;

	अगर (copy_to_user(user_buf, buf, buf_pos)) अणु
		ret = -EFAULT;
		जाओ out_buf;
	पूर्ण

	*ppos += buf_pos;
out_buf:
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations regmap_reg_ranges_fops = अणु
	.खोलो = simple_खोलो,
	.पढ़ो = regmap_reg_ranges_पढ़ो_file,
	.llseek = शेष_llseek,
पूर्ण;

अटल पूर्णांक regmap_access_show(काष्ठा seq_file *s, व्योम *ignored)
अणु
	काष्ठा regmap *map = s->निजी;
	पूर्णांक i, reg_len;

	reg_len = regmap_calc_reg_len(map->max_रेजिस्टर);

	क्रम (i = 0; i <= map->max_रेजिस्टर; i += map->reg_stride) अणु
		/* Ignore रेजिस्टरs which are neither पढ़ोable nor writable */
		अगर (!regmap_पढ़ोable(map, i) && !regmap_ग_लिखोable(map, i))
			जारी;

		/* Format the रेजिस्टर */
		seq_म_लिखो(s, "%.*x: %c %c %c %c\n", reg_len, i,
			   regmap_पढ़ोable(map, i) ? 'y' : 'n',
			   regmap_ग_लिखोable(map, i) ? 'y' : 'n',
			   regmap_अस्थिर(map, i) ? 'y' : 'n',
			   regmap_precious(map, i) ? 'y' : 'n');
	पूर्ण

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(regmap_access);

अटल sमाप_प्रकार regmap_cache_only_ग_लिखो_file(काष्ठा file *file,
					    स्थिर अक्षर __user *user_buf,
					    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा regmap *map = container_of(file->निजी_data,
					  काष्ठा regmap, cache_only);
	bool new_val, require_sync = false;
	पूर्णांक err;

	err = kstrtobool_from_user(user_buf, count, &new_val);
	/* Ignore malक्रमned data like debugfs_ग_लिखो_file_bool() */
	अगर (err)
		वापस count;

	err = debugfs_file_get(file->f_path.dentry);
	अगर (err)
		वापस err;

	map->lock(map->lock_arg);

	अगर (new_val && !map->cache_only) अणु
		dev_warn(map->dev, "debugfs cache_only=Y forced\n");
		add_taपूर्णांक(TAINT_USER, LOCKDEP_STILL_OK);
	पूर्ण अन्यथा अगर (!new_val && map->cache_only) अणु
		dev_warn(map->dev, "debugfs cache_only=N forced: syncing cache\n");
		require_sync = true;
	पूर्ण
	map->cache_only = new_val;

	map->unlock(map->lock_arg);
	debugfs_file_put(file->f_path.dentry);

	अगर (require_sync) अणु
		err = regcache_sync(map);
		अगर (err)
			dev_err(map->dev, "Failed to sync cache %d\n", err);
	पूर्ण

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations regmap_cache_only_fops = अणु
	.खोलो = simple_खोलो,
	.पढ़ो = debugfs_पढ़ो_file_bool,
	.ग_लिखो = regmap_cache_only_ग_लिखो_file,
पूर्ण;

अटल sमाप_प्रकार regmap_cache_bypass_ग_लिखो_file(काष्ठा file *file,
					      स्थिर अक्षर __user *user_buf,
					      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा regmap *map = container_of(file->निजी_data,
					  काष्ठा regmap, cache_bypass);
	bool new_val;
	पूर्णांक err;

	err = kstrtobool_from_user(user_buf, count, &new_val);
	/* Ignore malक्रमned data like debugfs_ग_लिखो_file_bool() */
	अगर (err)
		वापस count;

	err = debugfs_file_get(file->f_path.dentry);
	अगर (err)
		वापस err;

	map->lock(map->lock_arg);

	अगर (new_val && !map->cache_bypass) अणु
		dev_warn(map->dev, "debugfs cache_bypass=Y forced\n");
		add_taपूर्णांक(TAINT_USER, LOCKDEP_STILL_OK);
	पूर्ण अन्यथा अगर (!new_val && map->cache_bypass) अणु
		dev_warn(map->dev, "debugfs cache_bypass=N forced\n");
	पूर्ण
	map->cache_bypass = new_val;

	map->unlock(map->lock_arg);
	debugfs_file_put(file->f_path.dentry);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations regmap_cache_bypass_fops = अणु
	.खोलो = simple_खोलो,
	.पढ़ो = debugfs_पढ़ो_file_bool,
	.ग_लिखो = regmap_cache_bypass_ग_लिखो_file,
पूर्ण;

व्योम regmap_debugfs_init(काष्ठा regmap *map)
अणु
	काष्ठा rb_node *next;
	काष्ठा regmap_range_node *range_node;
	स्थिर अक्षर *devname = "dummy";
	स्थिर अक्षर *name = map->name;

	/*
	 * Userspace can initiate पढ़ोs from the hardware over debugfs.
	 * Normally पूर्णांकernal regmap काष्ठाures and buffers are रक्षित with
	 * a mutex or a spinlock, but अगर the regmap owner decided to disable
	 * all locking mechanisms, this is no दीर्घer the हाल. For safety:
	 * करोn't create the debugfs entries अगर locking is disabled.
	 */
	अगर (map->debugfs_disable) अणु
		dev_dbg(map->dev, "regmap locking disabled - not creating debugfs entries\n");
		वापस;
	पूर्ण

	/* If we करोn't have the debugfs root yet, postpone init */
	अगर (!regmap_debugfs_root) अणु
		काष्ठा regmap_debugfs_node *node;
		node = kzalloc(माप(*node), GFP_KERNEL);
		अगर (!node)
			वापस;
		node->map = map;
		mutex_lock(&regmap_debugfs_early_lock);
		list_add(&node->link, &regmap_debugfs_early_list);
		mutex_unlock(&regmap_debugfs_early_lock);
		वापस;
	पूर्ण

	INIT_LIST_HEAD(&map->debugfs_off_cache);
	mutex_init(&map->cache_lock);

	अगर (map->dev)
		devname = dev_name(map->dev);

	अगर (name) अणु
		अगर (!map->debugfs_name) अणु
			map->debugfs_name = kaप्र_लिखो(GFP_KERNEL, "%s-%s",
					      devname, name);
			अगर (!map->debugfs_name)
				वापस;
		पूर्ण
		name = map->debugfs_name;
	पूर्ण अन्यथा अणु
		name = devname;
	पूर्ण

	अगर (!म_भेद(name, "dummy")) अणु
		kमुक्त(map->debugfs_name);
		map->debugfs_name = kaप्र_लिखो(GFP_KERNEL, "dummy%d",
						dummy_index);
		अगर (!map->debugfs_name)
				वापस;
		name = map->debugfs_name;
		dummy_index++;
	पूर्ण

	map->debugfs = debugfs_create_dir(name, regmap_debugfs_root);

	debugfs_create_file("name", 0400, map->debugfs,
			    map, &regmap_name_fops);

	debugfs_create_file("range", 0400, map->debugfs,
			    map, &regmap_reg_ranges_fops);

	अगर (map->max_रेजिस्टर || regmap_पढ़ोable(map, 0)) अणु
		umode_t रेजिस्टरs_mode;

#अगर defined(REGMAP_ALLOW_WRITE_DEBUGFS)
		रेजिस्टरs_mode = 0600;
#अन्यथा
		रेजिस्टरs_mode = 0400;
#पूर्ण_अगर

		debugfs_create_file("registers", रेजिस्टरs_mode, map->debugfs,
				    map, &regmap_map_fops);
		debugfs_create_file("access", 0400, map->debugfs,
				    map, &regmap_access_fops);
	पूर्ण

	अगर (map->cache_type) अणु
		debugfs_create_file("cache_only", 0600, map->debugfs,
				    &map->cache_only, &regmap_cache_only_fops);
		debugfs_create_bool("cache_dirty", 0400, map->debugfs,
				    &map->cache_dirty);
		debugfs_create_file("cache_bypass", 0600, map->debugfs,
				    &map->cache_bypass,
				    &regmap_cache_bypass_fops);
	पूर्ण

	next = rb_first(&map->range_tree);
	जबतक (next) अणु
		range_node = rb_entry(next, काष्ठा regmap_range_node, node);

		अगर (range_node->name)
			debugfs_create_file(range_node->name, 0400,
					    map->debugfs, range_node,
					    &regmap_range_fops);

		next = rb_next(&range_node->node);
	पूर्ण

	अगर (map->cache_ops && map->cache_ops->debugfs_init)
		map->cache_ops->debugfs_init(map);
पूर्ण

व्योम regmap_debugfs_निकास(काष्ठा regmap *map)
अणु
	अगर (map->debugfs) अणु
		debugfs_हटाओ_recursive(map->debugfs);
		mutex_lock(&map->cache_lock);
		regmap_debugfs_मुक्त_dump_cache(map);
		mutex_unlock(&map->cache_lock);
		kमुक्त(map->debugfs_name);
		map->debugfs_name = शून्य;
	पूर्ण अन्यथा अणु
		काष्ठा regmap_debugfs_node *node, *पंचांगp;

		mutex_lock(&regmap_debugfs_early_lock);
		list_क्रम_each_entry_safe(node, पंचांगp, &regmap_debugfs_early_list,
					 link) अणु
			अगर (node->map == map) अणु
				list_del(&node->link);
				kमुक्त(node);
			पूर्ण
		पूर्ण
		mutex_unlock(&regmap_debugfs_early_lock);
	पूर्ण
पूर्ण

व्योम regmap_debugfs_initcall(व्योम)
अणु
	काष्ठा regmap_debugfs_node *node, *पंचांगp;

	regmap_debugfs_root = debugfs_create_dir("regmap", शून्य);

	mutex_lock(&regmap_debugfs_early_lock);
	list_क्रम_each_entry_safe(node, पंचांगp, &regmap_debugfs_early_list, link) अणु
		regmap_debugfs_init(node->map);
		list_del(&node->link);
		kमुक्त(node);
	पूर्ण
	mutex_unlock(&regmap_debugfs_early_lock);
पूर्ण
