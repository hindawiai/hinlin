<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * (C) Copyright David Gibson <dwg@au1.ibm.com>, IBM Corporation.  2005.
 */

#समावेश "dtc.h"

#समावेश <dirent.h>
#समावेश <sys/स्थिति.स>

अटल काष्ठा node *पढ़ो_fstree(स्थिर अक्षर *स_नाम)
अणु
	सूची *d;
	काष्ठा dirent *de;
	काष्ठा stat st;
	काष्ठा node *tree;

	d = सूची_खोलो(स_नाम);
	अगर (!d)
		die("Couldn't opendir() \"%s\": %s\n", स_नाम, म_त्रुटि(त्रुटि_सं));

	tree = build_node(शून्य, शून्य, शून्य);

	जबतक ((de = सूची_पढ़ो(d)) != शून्य) अणु
		अक्षर *क्षणिकe;

		अगर (streq(de->d_name, ".")
		    || streq(de->d_name, ".."))
			जारी;

		क्षणिकe = join_path(स_नाम, de->d_name);

		अगर (stat(क्षणिकe, &st) < 0)
			die("stat(%s): %s\n", क्षणिकe, म_त्रुटि(त्रुटि_सं));

		अगर (S_ISREG(st.st_mode)) अणु
			काष्ठा property *prop;
			खाता *pfile;

			pfile = ख_खोलो(क्षणिकe, "rb");
			अगर (! pfile) अणु
				ख_लिखो(मानक_त्रुटि,
					"WARNING: Cannot open %s: %s\n",
					क्षणिकe, म_त्रुटि(त्रुटि_सं));
			पूर्ण अन्यथा अणु
				prop = build_property(xstrdup(de->d_name),
						      data_copy_file(pfile,
								     st.st_size),
						      शून्य);
				add_property(tree, prop);
				ख_बंद(pfile);
			पूर्ण
		पूर्ण अन्यथा अगर (S_ISसूची(st.st_mode)) अणु
			काष्ठा node *newchild;

			newchild = पढ़ो_fstree(क्षणिकe);
			newchild = name_node(newchild, xstrdup(de->d_name));
			add_child(tree, newchild);
		पूर्ण

		मुक्त(क्षणिकe);
	पूर्ण

	बंद_सूची(d);
	वापस tree;
पूर्ण

काष्ठा dt_info *dt_from_fs(स्थिर अक्षर *स_नाम)
अणु
	काष्ठा node *tree;

	tree = पढ़ो_fstree(स_नाम);
	tree = name_node(tree, "");

	वापस build_dt_info(DTSF_V1, शून्य, tree, guess_boot_cpuid(tree));
पूर्ण
