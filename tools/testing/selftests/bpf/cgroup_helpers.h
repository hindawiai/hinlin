<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __CGROUP_HELPERS_H
#घोषणा __CGROUP_HELPERS_H
#समावेश <त्रुटिसं.स>
#समावेश <माला.स>

#घोषणा clean_त्रुटि_सं() (त्रुटि_सं == 0 ? "None" : म_त्रुटि(त्रुटि_सं))
#घोषणा log_err(MSG, ...) ख_लिखो(मानक_त्रुटि, "(%s:%d: errno: %s) " MSG "\n", \
	__खाता__, __LINE__, clean_त्रुटि_सं(), ##__VA_ARGS__)


पूर्णांक cgroup_setup_and_join(स्थिर अक्षर *path);
पूर्णांक create_and_get_cgroup(स्थिर अक्षर *path);
पूर्णांक join_cgroup(स्थिर अक्षर *path);
पूर्णांक setup_cgroup_environment(व्योम);
व्योम cleanup_cgroup_environment(व्योम);
अचिन्हित दीर्घ दीर्घ get_cgroup_id(स्थिर अक्षर *path);

#पूर्ण_अगर
