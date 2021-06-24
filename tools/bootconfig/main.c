<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Boot config tool क्रम initrd image
 */
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <unistd.h>
#समावेश <माला.स>
#समावेश <त्रुटिसं.स>
#समावेश <endian.h>

#समावेश <linux/kernel.h>
#समावेश <linux/bootconfig.h>

अटल पूर्णांक xbc_show_value(काष्ठा xbc_node *node, bool semicolon)
अणु
	स्थिर अक्षर *val, *eol;
	अक्षर q;
	पूर्णांक i = 0;

	eol = semicolon ? ";\n" : "\n";
	xbc_array_क्रम_each_value(node, val) अणु
		अगर (म_अक्षर(val, '"'))
			q = '\'';
		अन्यथा
			q = '"';
		म_लिखो("%c%s%c%s", q, val, q, node->next ? ", " : eol);
		i++;
	पूर्ण
	वापस i;
पूर्ण

अटल व्योम xbc_show_compact_tree(व्योम)
अणु
	काष्ठा xbc_node *node, *cnode;
	पूर्णांक depth = 0, i;

	node = xbc_root_node();
	जबतक (node && xbc_node_is_key(node)) अणु
		क्रम (i = 0; i < depth; i++)
			म_लिखो("\t");
		cnode = xbc_node_get_child(node);
		जबतक (cnode && xbc_node_is_key(cnode) && !cnode->next) अणु
			म_लिखो("%s.", xbc_node_get_data(node));
			node = cnode;
			cnode = xbc_node_get_child(node);
		पूर्ण
		अगर (cnode && xbc_node_is_key(cnode)) अणु
			म_लिखो("%s {\n", xbc_node_get_data(node));
			depth++;
			node = cnode;
			जारी;
		पूर्ण अन्यथा अगर (cnode && xbc_node_is_value(cnode)) अणु
			म_लिखो("%s = ", xbc_node_get_data(node));
			xbc_show_value(cnode, true);
		पूर्ण अन्यथा अणु
			म_लिखो("%s;\n", xbc_node_get_data(node));
		पूर्ण

		अगर (node->next) अणु
			node = xbc_node_get_next(node);
			जारी;
		पूर्ण
		जबतक (!node->next) अणु
			node = xbc_node_get_parent(node);
			अगर (!node)
				वापस;
			अगर (!xbc_node_get_child(node)->next)
				जारी;
			depth--;
			क्रम (i = 0; i < depth; i++)
				म_लिखो("\t");
			म_लिखो("}\n");
		पूर्ण
		node = xbc_node_get_next(node);
	पूर्ण
पूर्ण

अटल व्योम xbc_show_list(व्योम)
अणु
	अक्षर key[XBC_KEYLEN_MAX];
	काष्ठा xbc_node *leaf;
	स्थिर अक्षर *val;
	पूर्णांक ret = 0;

	xbc_क्रम_each_key_value(leaf, val) अणु
		ret = xbc_node_compose_key(leaf, key, XBC_KEYLEN_MAX);
		अगर (ret < 0)
			अवरोध;
		म_लिखो("%s = ", key);
		अगर (!val || val[0] == '\0') अणु
			म_लिखो("\"\"\n");
			जारी;
		पूर्ण
		xbc_show_value(xbc_node_get_child(leaf), false);
	पूर्ण
पूर्ण

/* Simple real checksum */
अटल पूर्णांक checksum(अचिन्हित अक्षर *buf, पूर्णांक len)
अणु
	पूर्णांक i, sum = 0;

	क्रम (i = 0; i < len; i++)
		sum += buf[i];

	वापस sum;
पूर्ण

#घोषणा PAGE_SIZE	4096

अटल पूर्णांक load_xbc_fd(पूर्णांक fd, अक्षर **buf, पूर्णांक size)
अणु
	पूर्णांक ret;

	*buf = दो_स्मृति(size + 1);
	अगर (!*buf)
		वापस -ENOMEM;

	ret = पढ़ो(fd, *buf, size);
	अगर (ret < 0)
		वापस -त्रुटि_सं;
	(*buf)[size] = '\0';

	वापस ret;
पूर्ण

/* Return the पढ़ो size or -त्रुटि_सं */
अटल पूर्णांक load_xbc_file(स्थिर अक्षर *path, अक्षर **buf)
अणु
	काष्ठा stat stat;
	पूर्णांक fd, ret;

	fd = खोलो(path, O_RDONLY);
	अगर (fd < 0)
		वापस -त्रुटि_सं;
	ret = ख_स्थिति(fd, &stat);
	अगर (ret < 0)
		वापस -त्रुटि_सं;

	ret = load_xbc_fd(fd, buf, stat.st_size);

	बंद(fd);

	वापस ret;
पूर्ण

अटल पूर्णांक pr_त्रुटि_सं(स्थिर अक्षर *msg, पूर्णांक err)
अणु
	pr_err("%s: %d\n", msg, err);
	वापस err;
पूर्ण

अटल पूर्णांक load_xbc_from_initrd(पूर्णांक fd, अक्षर **buf)
अणु
	काष्ठा stat stat;
	पूर्णांक ret;
	u32 size = 0, csum = 0, rcsum;
	अक्षर magic[BOOTCONFIG_MAGIC_LEN];
	स्थिर अक्षर *msg;

	ret = ख_स्थिति(fd, &stat);
	अगर (ret < 0)
		वापस -त्रुटि_सं;

	अगर (stat.st_size < 8 + BOOTCONFIG_MAGIC_LEN)
		वापस 0;

	अगर (lseek(fd, -BOOTCONFIG_MAGIC_LEN, अंत_से) < 0)
		वापस pr_त्रुटि_सं("Failed to lseek for magic", -त्रुटि_सं);

	अगर (पढ़ो(fd, magic, BOOTCONFIG_MAGIC_LEN) < 0)
		वापस pr_त्रुटि_सं("Failed to read", -त्रुटि_सं);

	/* Check the bootconfig magic bytes */
	अगर (स_भेद(magic, BOOTCONFIG_MAGIC, BOOTCONFIG_MAGIC_LEN) != 0)
		वापस 0;

	अगर (lseek(fd, -(8 + BOOTCONFIG_MAGIC_LEN), अंत_से) < 0)
		वापस pr_त्रुटि_सं("Failed to lseek for size", -त्रुटि_सं);

	अगर (पढ़ो(fd, &size, माप(u32)) < 0)
		वापस pr_त्रुटि_सं("Failed to read size", -त्रुटि_सं);
	size = le32toh(size);

	अगर (पढ़ो(fd, &csum, माप(u32)) < 0)
		वापस pr_त्रुटि_सं("Failed to read checksum", -त्रुटि_सं);
	csum = le32toh(csum);

	/* Wrong size error  */
	अगर (stat.st_size < size + 8 + BOOTCONFIG_MAGIC_LEN) अणु
		pr_err("bootconfig size is too big\n");
		वापस -E2BIG;
	पूर्ण

	अगर (lseek(fd, stat.st_size - (size + 8 + BOOTCONFIG_MAGIC_LEN),
		  शुरू_से) < 0)
		वापस pr_त्रुटि_सं("Failed to lseek", -त्रुटि_सं);

	ret = load_xbc_fd(fd, buf, size);
	अगर (ret < 0)
		वापस ret;

	/* Wrong Checksum */
	rcsum = checksum((अचिन्हित अक्षर *)*buf, size);
	अगर (csum != rcsum) अणु
		pr_err("checksum error: %d != %d\n", csum, rcsum);
		वापस -EINVAL;
	पूर्ण

	ret = xbc_init(*buf, &msg, शून्य);
	/* Wrong data */
	अगर (ret < 0) अणु
		pr_err("parse error: %s.\n", msg);
		वापस ret;
	पूर्ण

	वापस size;
पूर्ण

अटल व्योम show_xbc_error(स्थिर अक्षर *data, स्थिर अक्षर *msg, पूर्णांक pos)
अणु
	पूर्णांक lin = 1, col, i;

	अगर (pos < 0) अणु
		pr_err("Error: %s.\n", msg);
		वापस;
	पूर्ण

	/* Note that pos starts from 0 but lin and col should start from 1. */
	col = pos + 1;
	क्रम (i = 0; i < pos; i++) अणु
		अगर (data[i] == '\n') अणु
			lin++;
			col = pos - i;
		पूर्ण
	पूर्ण
	pr_err("Parse Error: %s at %d:%d\n", msg, lin, col);

पूर्ण

अटल पूर्णांक init_xbc_with_error(अक्षर *buf, पूर्णांक len)
अणु
	अक्षर *copy = strdup(buf);
	स्थिर अक्षर *msg;
	पूर्णांक ret, pos;

	अगर (!copy)
		वापस -ENOMEM;

	ret = xbc_init(buf, &msg, &pos);
	अगर (ret < 0)
		show_xbc_error(copy, msg, pos);
	मुक्त(copy);

	वापस ret;
पूर्ण

अटल पूर्णांक show_xbc(स्थिर अक्षर *path, bool list)
अणु
	पूर्णांक ret, fd;
	अक्षर *buf = शून्य;
	काष्ठा stat st;

	ret = stat(path, &st);
	अगर (ret < 0) अणु
		ret = -त्रुटि_सं;
		pr_err("Failed to stat %s: %d\n", path, ret);
		वापस ret;
	पूर्ण

	fd = खोलो(path, O_RDONLY);
	अगर (fd < 0) अणु
		ret = -त्रुटि_सं;
		pr_err("Failed to open initrd %s: %d\n", path, ret);
		वापस ret;
	पूर्ण

	ret = load_xbc_from_initrd(fd, &buf);
	बंद(fd);
	अगर (ret < 0) अणु
		pr_err("Failed to load a boot config from initrd: %d\n", ret);
		जाओ out;
	पूर्ण
	/* Assume a bootconfig file अगर it is enough small */
	अगर (ret == 0 && st.st_size <= XBC_DATA_MAX) अणु
		ret = load_xbc_file(path, &buf);
		अगर (ret < 0) अणु
			pr_err("Failed to load a boot config: %d\n", ret);
			जाओ out;
		पूर्ण
		अगर (init_xbc_with_error(buf, ret) < 0)
			जाओ out;
	पूर्ण
	अगर (list)
		xbc_show_list();
	अन्यथा
		xbc_show_compact_tree();
	ret = 0;
out:
	मुक्त(buf);

	वापस ret;
पूर्ण

अटल पूर्णांक delete_xbc(स्थिर अक्षर *path)
अणु
	काष्ठा stat stat;
	पूर्णांक ret = 0, fd, size;
	अक्षर *buf = शून्य;

	fd = खोलो(path, O_RDWR);
	अगर (fd < 0) अणु
		ret = -त्रुटि_सं;
		pr_err("Failed to open initrd %s: %d\n", path, ret);
		वापस ret;
	पूर्ण

	size = load_xbc_from_initrd(fd, &buf);
	अगर (size < 0) अणु
		ret = size;
		pr_err("Failed to load a boot config from initrd: %d\n", ret);
	पूर्ण अन्यथा अगर (size > 0) अणु
		ret = ख_स्थिति(fd, &stat);
		अगर (!ret)
			ret = ftruncate(fd, stat.st_size
					- size - 8 - BOOTCONFIG_MAGIC_LEN);
		अगर (ret)
			ret = -त्रुटि_सं;
	पूर्ण /* Ignore अगर there is no boot config in initrd */

	बंद(fd);
	मुक्त(buf);

	वापस ret;
पूर्ण

अटल पूर्णांक apply_xbc(स्थिर अक्षर *path, स्थिर अक्षर *xbc_path)
अणु
	अक्षर *buf, *data, *p;
	माप_प्रकार total_size;
	काष्ठा stat stat;
	स्थिर अक्षर *msg;
	u32 size, csum;
	पूर्णांक pos, pad;
	पूर्णांक ret, fd;

	ret = load_xbc_file(xbc_path, &buf);
	अगर (ret < 0) अणु
		pr_err("Failed to load %s : %d\n", xbc_path, ret);
		वापस ret;
	पूर्ण
	size = म_माप(buf) + 1;
	csum = checksum((अचिन्हित अक्षर *)buf, size);

	/* Backup the bootconfig data */
	data = सुस्मृति(size + BOOTCONFIG_ALIGN +
		      माप(u32) + माप(u32) + BOOTCONFIG_MAGIC_LEN, 1);
	अगर (!data)
		वापस -ENOMEM;
	स_नकल(data, buf, size);

	/* Check the data क्रमmat */
	ret = xbc_init(buf, &msg, &pos);
	अगर (ret < 0) अणु
		show_xbc_error(data, msg, pos);
		मुक्त(data);
		मुक्त(buf);

		वापस ret;
	पूर्ण
	म_लिखो("Apply %s to %s\n", xbc_path, path);
	म_लिखो("\tNumber of nodes: %d\n", ret);
	म_लिखो("\tSize: %u bytes\n", (अचिन्हित पूर्णांक)size);
	म_लिखो("\tChecksum: %d\n", (अचिन्हित पूर्णांक)csum);

	/* TODO: Check the options by schema */
	xbc_destroy_all();
	मुक्त(buf);

	/* Remove old boot config अगर exists */
	ret = delete_xbc(path);
	अगर (ret < 0) अणु
		pr_err("Failed to delete previous boot config: %d\n", ret);
		मुक्त(data);
		वापस ret;
	पूर्ण

	/* Apply new one */
	fd = खोलो(path, O_RDWR | O_APPEND);
	अगर (fd < 0) अणु
		ret = -त्रुटि_सं;
		pr_err("Failed to open %s: %d\n", path, ret);
		मुक्त(data);
		वापस ret;
	पूर्ण
	/* TODO: Ensure the @path is initramfs/initrd image */
	अगर (ख_स्थिति(fd, &stat) < 0) अणु
		ret = -त्रुटि_सं;
		pr_err("Failed to get the size of %s\n", path);
		जाओ out;
	पूर्ण

	/* To align up the total size to BOOTCONFIG_ALIGN, get padding size */
	total_size = stat.st_size + size + माप(u32) * 2 + BOOTCONFIG_MAGIC_LEN;
	pad = ((total_size + BOOTCONFIG_ALIGN - 1) & (~BOOTCONFIG_ALIGN_MASK)) - total_size;
	size += pad;

	/* Add a footer */
	p = data + size;
	*(u32 *)p = htole32(size);
	p += माप(u32);

	*(u32 *)p = htole32(csum);
	p += माप(u32);

	स_नकल(p, BOOTCONFIG_MAGIC, BOOTCONFIG_MAGIC_LEN);
	p += BOOTCONFIG_MAGIC_LEN;

	total_size = p - data;

	ret = ग_लिखो(fd, data, total_size);
	अगर (ret < total_size) अणु
		अगर (ret < 0)
			ret = -त्रुटि_सं;
		pr_err("Failed to apply a boot config: %d\n", ret);
		अगर (ret >= 0)
			जाओ out_rollback;
	पूर्ण अन्यथा
		ret = 0;

out:
	बंद(fd);
	मुक्त(data);

	वापस ret;

out_rollback:
	/* Map the partial ग_लिखो to -ENOSPC */
	अगर (ret >= 0)
		ret = -ENOSPC;
	अगर (ftruncate(fd, stat.st_size) < 0) अणु
		ret = -त्रुटि_सं;
		pr_err("Failed to rollback the write error: %d\n", ret);
		pr_err("The initrd %s may be corrupted. Recommend to rebuild.\n", path);
	पूर्ण
	जाओ out;
पूर्ण

अटल पूर्णांक usage(व्योम)
अणु
	म_लिखो("Usage: bootconfig [OPTIONS] <INITRD>\n"
		"Or     bootconfig <CONFIG>\n"
		" Apply, delete or show boot config to initrd.\n"
		" Options:\n"
		"		-a <config>: Apply boot config to initrd\n"
		"		-d : Delete boot config file from initrd\n"
		"		-l : list boot config in initrd or file\n\n"
		" If no option is given, show the bootconfig in the given file.\n");
	वापस -1;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	अक्षर *path = शून्य;
	अक्षर *apply = शून्य;
	bool delete = false, list = false;
	पूर्णांक opt;

	जबतक ((opt = getopt(argc, argv, "hda:l")) != -1) अणु
		चयन (opt) अणु
		हाल 'd':
			delete = true;
			अवरोध;
		हाल 'a':
			apply = optarg;
			अवरोध;
		हाल 'l':
			list = true;
			अवरोध;
		हाल 'h':
		शेष:
			वापस usage();
		पूर्ण
	पूर्ण

	अगर ((apply && delete) || (delete && list) || (apply && list)) अणु
		pr_err("Error: You can give one of -a, -d or -l at once.\n");
		वापस usage();
	पूर्ण

	अगर (optind >= argc) अणु
		pr_err("Error: No initrd is specified.\n");
		वापस usage();
	पूर्ण

	path = argv[optind];

	अगर (apply)
		वापस apply_xbc(path, apply);
	अन्यथा अगर (delete)
		वापस delete_xbc(path);

	वापस show_xbc(path, list);
पूर्ण
