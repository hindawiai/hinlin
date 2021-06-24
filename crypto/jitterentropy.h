<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

बाह्य व्योम *jent_zalloc(अचिन्हित पूर्णांक len);
बाह्य व्योम jent_zमुक्त(व्योम *ptr);
बाह्य पूर्णांक jent_fips_enabled(व्योम);
बाह्य व्योम jent_panic(अक्षर *s);
बाह्य व्योम jent_स_नकल(व्योम *dest, स्थिर व्योम *src, अचिन्हित पूर्णांक n);
बाह्य व्योम jent_get_nsसमय(__u64 *out);

काष्ठा अक्रम_data;
बाह्य पूर्णांक jent_entropy_init(व्योम);
बाह्य पूर्णांक jent_पढ़ो_entropy(काष्ठा अक्रम_data *ec, अचिन्हित अक्षर *data,
			     अचिन्हित पूर्णांक len);

बाह्य काष्ठा अक्रम_data *jent_entropy_collector_alloc(अचिन्हित पूर्णांक osr,
						      अचिन्हित पूर्णांक flags);
बाह्य व्योम jent_entropy_collector_मुक्त(काष्ठा अक्रम_data *entropy_collector);
