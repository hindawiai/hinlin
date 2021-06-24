<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_DATA_H
#घोषणा __PERF_DATA_H

#समावेश <मानकपन.स>
#समावेश <stdbool.h>

क्रमागत perf_data_mode अणु
	PERF_DATA_MODE_WRITE,
	PERF_DATA_MODE_READ,
पूर्ण;

क्रमागत perf_dir_version अणु
	PERF_सूची_SINGLE_खाता	= 0,
	PERF_सूची_VERSION	= 1,
पूर्ण;

काष्ठा perf_data_file अणु
	अक्षर		*path;
	जोड़ अणु
		पूर्णांक	 fd;
		खाता	*fptr;
	पूर्ण;
	अचिन्हित दीर्घ	 size;
पूर्ण;

काष्ठा perf_data अणु
	स्थिर अक्षर		*path;
	काष्ठा perf_data_file	 file;
	bool			 is_pipe;
	bool			 is_dir;
	bool			 क्रमce;
	bool			 use_stdio;
	क्रमागत perf_data_mode	 mode;

	काष्ठा अणु
		u64			 version;
		काष्ठा perf_data_file	*files;
		पूर्णांक			 nr;
	पूर्ण dir;
पूर्ण;

अटल अंतरभूत bool perf_data__is_पढ़ो(काष्ठा perf_data *data)
अणु
	वापस data->mode == PERF_DATA_MODE_READ;
पूर्ण

अटल अंतरभूत bool perf_data__is_ग_लिखो(काष्ठा perf_data *data)
अणु
	वापस data->mode == PERF_DATA_MODE_WRITE;
पूर्ण

अटल अंतरभूत पूर्णांक perf_data__is_pipe(काष्ठा perf_data *data)
अणु
	वापस data->is_pipe;
पूर्ण

अटल अंतरभूत bool perf_data__is_dir(काष्ठा perf_data *data)
अणु
	वापस data->is_dir;
पूर्ण

अटल अंतरभूत bool perf_data__is_single_file(काष्ठा perf_data *data)
अणु
	वापस data->dir.version == PERF_सूची_SINGLE_खाता;
पूर्ण

अटल अंतरभूत पूर्णांक perf_data__fd(काष्ठा perf_data *data)
अणु
	अगर (data->use_stdio)
		वापस fileno(data->file.fptr);

	वापस data->file.fd;
पूर्ण

पूर्णांक perf_data__खोलो(काष्ठा perf_data *data);
व्योम perf_data__बंद(काष्ठा perf_data *data);
sमाप_प्रकार perf_data__पढ़ो(काष्ठा perf_data *data, व्योम *buf, माप_प्रकार size);
sमाप_प्रकार perf_data__ग_लिखो(काष्ठा perf_data *data,
			      व्योम *buf, माप_प्रकार size);
sमाप_प्रकार perf_data_file__ग_लिखो(काष्ठा perf_data_file *file,
			      व्योम *buf, माप_प्रकार size);
/*
 * If at_निकास is set, only नाम current perf.data to
 * perf.data.<postfix>, जारी ग_लिखो on original data.
 * Set at_निकास when flushing the last output.
 *
 * Return value is fd of new output.
 */
पूर्णांक perf_data__चयन(काष्ठा perf_data *data,
			   स्थिर अक्षर *postfix,
			   माप_प्रकार pos, bool at_निकास, अक्षर **new_filepath);

पूर्णांक perf_data__create_dir(काष्ठा perf_data *data, पूर्णांक nr);
पूर्णांक perf_data__खोलो_dir(काष्ठा perf_data *data);
व्योम perf_data__बंद_dir(काष्ठा perf_data *data);
पूर्णांक perf_data__update_dir(काष्ठा perf_data *data);
अचिन्हित दीर्घ perf_data__size(काष्ठा perf_data *data);
पूर्णांक perf_data__make_kcore_dir(काष्ठा perf_data *data, अक्षर *buf, माप_प्रकार buf_sz);
अक्षर *perf_data__kallsyms_name(काष्ठा perf_data *data);
bool is_perf_data(स्थिर अक्षर *path);
#पूर्ण_अगर /* __PERF_DATA_H */
