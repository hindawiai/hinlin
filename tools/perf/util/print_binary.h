<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित PERF_PRINT_BINARY_H
#घोषणा PERF_PRINT_BINARY_H

#समावेश <मानकघोष.स>
#समावेश <मानकपन.स>

क्रमागत binary_prपूर्णांकer_ops अणु
	BINARY_PRINT_DATA_BEGIN,
	BINARY_PRINT_LINE_BEGIN,
	BINARY_PRINT_ADDR,
	BINARY_PRINT_NUM_DATA,
	BINARY_PRINT_NUM_PAD,
	BINARY_PRINT_SEP,
	BINARY_PRINT_CHAR_DATA,
	BINARY_PRINT_CHAR_PAD,
	BINARY_PRINT_LINE_END,
	BINARY_PRINT_DATA_END,
पूर्ण;

प्रकार पूर्णांक (*binary__ख_लिखो_t)(क्रमागत binary_prपूर्णांकer_ops op,
				 अचिन्हित पूर्णांक val, व्योम *extra, खाता *fp);

पूर्णांक binary__ख_लिखो(अचिन्हित अक्षर *data, माप_प्रकार len,
		    माप_प्रकार bytes_per_line, binary__ख_लिखो_t prपूर्णांकer,
		    व्योम *extra, खाता *fp);

अटल अंतरभूत व्योम prपूर्णांक_binary(अचिन्हित अक्षर *data, माप_प्रकार len,
				माप_प्रकार bytes_per_line, binary__ख_लिखो_t prपूर्णांकer,
				व्योम *extra)
अणु
	binary__ख_लिखो(data, len, bytes_per_line, prपूर्णांकer, extra, मानक_निकास);
पूर्ण

पूर्णांक is_prपूर्णांकable_array(अक्षर *p, अचिन्हित पूर्णांक len);

#पूर्ण_अगर /* PERF_PRINT_BINARY_H */
