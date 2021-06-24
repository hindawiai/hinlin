<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Vidtv serves as a reference DVB driver and helps validate the existing APIs
 * in the media subप्रणाली. It can also aid developers working on userspace
 * applications.
 *
 * This file contains the code क्रम a 'channel' असलtraction.
 *
 * When vidtv boots, it will create some hardcoded channels.
 * Their services will be concatenated to populate the SDT.
 * Their programs will be concatenated to populate the PAT
 * Their events will be concatenated to populate the EIT
 * For each program in the PAT, a PMT section will be created
 * The PMT section क्रम a channel will be asचिन्हित its streams.
 * Every stream will have its corresponding encoder polled to produce TS packets
 * These packets may be पूर्णांकerleaved by the mux and then delivered to the bridge
 *
 *
 * Copyright (C) 2020 Daniel W. S. Almeida
 */

#समावेश <linux/dev_prपूर्णांकk.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

#समावेश "vidtv_channel.h"
#समावेश "vidtv_common.h"
#समावेश "vidtv_encoder.h"
#समावेश "vidtv_mux.h"
#समावेश "vidtv_psi.h"
#समावेश "vidtv_s302m.h"

अटल व्योम vidtv_channel_encoder_destroy(काष्ठा vidtv_encoder *e)
अणु
	काष्ठा vidtv_encoder *पंचांगp = शून्य;
	काष्ठा vidtv_encoder *curr = e;

	जबतक (curr) अणु
		/* क्रमward the call to the derived type */
		पंचांगp = curr;
		curr = curr->next;
		पंचांगp->destroy(पंचांगp);
	पूर्ण
पूर्ण

#घोषणा ENCODING_ISO8859_15 "\x0b"
#घोषणा TS_NIT_PID	0x10

/*
 * init an audio only channel with a s302m encoder
 */
काष्ठा vidtv_channel
*vidtv_channel_s302m_init(काष्ठा vidtv_channel *head, u16 transport_stream_id)
अणु
	स्थिर __be32 s302m_fid              = cpu_to_be32(VIDTV_S302M_FORMAT_IDENTIFIER);
	अक्षर *event_text = ENCODING_ISO8859_15 "Bagatelle No. 25 in A minor for solo piano, also known as F\xfcr Elise, composed by Ludwig van Beethoven";
	अक्षर *event_name = ENCODING_ISO8859_15 "Ludwig van Beethoven: F\xfcr Elise";
	काष्ठा vidtv_s302m_encoder_init_args encoder_args = अणुपूर्ण;
	अक्षर *iso_language_code = ENCODING_ISO8859_15 "eng";
	अक्षर *provider = ENCODING_ISO8859_15 "LinuxTV.org";
	अक्षर *name = ENCODING_ISO8859_15 "Beethoven";
	स्थिर u16 s302m_es_pid              = 0x111; /* packet id क्रम the ES */
	स्थिर u16 s302m_program_pid         = 0x101; /* packet id क्रम PMT*/
	स्थिर u16 s302m_service_id          = 0x880;
	स्थिर u16 s302m_program_num         = 0x880;
	स्थिर u16 s302m_beethoven_event_id  = 1;
	काष्ठा vidtv_channel *s302m;

	s302m = kzalloc(माप(*s302m), GFP_KERNEL);
	अगर (!s302m)
		वापस शून्य;

	s302m->name = kstrdup(name, GFP_KERNEL);
	अगर (!s302m->name)
		जाओ मुक्त_s302m;

	s302m->service = vidtv_psi_sdt_service_init(शून्य, s302m_service_id, false, true);
	अगर (!s302m->service)
		जाओ मुक्त_name;

	s302m->service->descriptor = (काष्ठा vidtv_psi_desc *)
				     vidtv_psi_service_desc_init(शून्य,
								 DIGITAL_RADIO_SOUND_SERVICE,
								 name,
								 provider);
	अगर (!s302m->service->descriptor)
		जाओ मुक्त_service;

	s302m->transport_stream_id = transport_stream_id;

	s302m->program = vidtv_psi_pat_program_init(शून्य,
						    s302m_service_id,
						    s302m_program_pid);
	अगर (!s302m->program)
		जाओ मुक्त_service;

	s302m->program_num = s302m_program_num;

	s302m->streams = vidtv_psi_pmt_stream_init(शून्य,
						   STREAM_PRIVATE_DATA,
						   s302m_es_pid);
	अगर (!s302m->streams)
		जाओ मुक्त_program;

	s302m->streams->descriptor = (काष्ठा vidtv_psi_desc *)
				     vidtv_psi_registration_desc_init(शून्य,
								      s302m_fid,
								      शून्य,
								      0);
	अगर (!s302m->streams->descriptor)
		जाओ मुक्त_streams;

	encoder_args.es_pid = s302m_es_pid;

	s302m->encoders = vidtv_s302m_encoder_init(encoder_args);
	अगर (!s302m->encoders)
		जाओ मुक्त_streams;

	s302m->events = vidtv_psi_eit_event_init(शून्य, s302m_beethoven_event_id);
	अगर (!s302m->events)
		जाओ मुक्त_encoders;
	s302m->events->descriptor = (काष्ठा vidtv_psi_desc *)
				    vidtv_psi_लघु_event_desc_init(शून्य,
								    iso_language_code,
								    event_name,
								    event_text);
	अगर (!s302m->events->descriptor)
		जाओ मुक्त_events;

	अगर (head) अणु
		जबतक (head->next)
			head = head->next;

		head->next = s302m;
	पूर्ण

	वापस s302m;

मुक्त_events:
	vidtv_psi_eit_event_destroy(s302m->events);
मुक्त_encoders:
	vidtv_s302m_encoder_destroy(s302m->encoders);
मुक्त_streams:
	vidtv_psi_pmt_stream_destroy(s302m->streams);
मुक्त_program:
	vidtv_psi_pat_program_destroy(s302m->program);
मुक्त_service:
	vidtv_psi_sdt_service_destroy(s302m->service);
मुक्त_name:
	kमुक्त(s302m->name);
मुक्त_s302m:
	kमुक्त(s302m);

	वापस शून्य;
पूर्ण

अटल काष्ठा vidtv_psi_table_eit_event
*vidtv_channel_eit_event_cat_पूर्णांकo_new(काष्ठा vidtv_mux *m)
अणु
	/* Concatenate the events */
	स्थिर काष्ठा vidtv_channel *cur_chnl = m->channels;
	काष्ठा vidtv_psi_table_eit_event *curr = शून्य;
	काष्ठा vidtv_psi_table_eit_event *head = शून्य;
	काष्ठा vidtv_psi_table_eit_event *tail = शून्य;
	काष्ठा vidtv_psi_desc *desc = शून्य;
	u16 event_id;

	अगर (!cur_chnl)
		वापस शून्य;

	जबतक (cur_chnl) अणु
		curr = cur_chnl->events;

		अगर (!curr)
			dev_warn_ratelimited(m->dev,
					     "No events found for channel %s\n",
					     cur_chnl->name);

		जबतक (curr) अणु
			event_id = be16_to_cpu(curr->event_id);
			tail = vidtv_psi_eit_event_init(tail, event_id);
			अगर (!tail) अणु
				vidtv_psi_eit_event_destroy(head);
				वापस शून्य;
			पूर्ण

			desc = vidtv_psi_desc_clone(curr->descriptor);
			vidtv_psi_desc_assign(&tail->descriptor, desc);

			अगर (!head)
				head = tail;

			curr = curr->next;
		पूर्ण

		cur_chnl = cur_chnl->next;
	पूर्ण

	वापस head;
पूर्ण

अटल काष्ठा vidtv_psi_table_sdt_service
*vidtv_channel_sdt_serv_cat_पूर्णांकo_new(काष्ठा vidtv_mux *m)
अणु
	/* Concatenate the services */
	स्थिर काष्ठा vidtv_channel *cur_chnl = m->channels;

	काष्ठा vidtv_psi_table_sdt_service *curr = शून्य;
	काष्ठा vidtv_psi_table_sdt_service *head = शून्य;
	काष्ठा vidtv_psi_table_sdt_service *tail = शून्य;

	काष्ठा vidtv_psi_desc *desc = शून्य;
	u16 service_id;

	अगर (!cur_chnl)
		वापस शून्य;

	जबतक (cur_chnl) अणु
		curr = cur_chnl->service;

		अगर (!curr)
			dev_warn_ratelimited(m->dev,
					     "No services found for channel %s\n",
					     cur_chnl->name);

		जबतक (curr) अणु
			service_id = be16_to_cpu(curr->service_id);
			tail = vidtv_psi_sdt_service_init(tail,
							  service_id,
							  curr->EIT_schedule,
							  curr->EIT_present_following);
			अगर (!tail)
				जाओ मुक्त;

			desc = vidtv_psi_desc_clone(curr->descriptor);
			अगर (!desc)
				जाओ मुक्त_tail;
			vidtv_psi_desc_assign(&tail->descriptor, desc);

			अगर (!head)
				head = tail;

			curr = curr->next;
		पूर्ण

		cur_chnl = cur_chnl->next;
	पूर्ण

	वापस head;

मुक्त_tail:
	vidtv_psi_sdt_service_destroy(tail);
मुक्त:
	vidtv_psi_sdt_service_destroy(head);
	वापस शून्य;
पूर्ण

अटल काष्ठा vidtv_psi_table_pat_program*
vidtv_channel_pat_prog_cat_पूर्णांकo_new(काष्ठा vidtv_mux *m)
अणु
	/* Concatenate the programs */
	स्थिर काष्ठा vidtv_channel *cur_chnl = m->channels;
	काष्ठा vidtv_psi_table_pat_program *curr = शून्य;
	काष्ठा vidtv_psi_table_pat_program *head = शून्य;
	काष्ठा vidtv_psi_table_pat_program *tail = शून्य;
	u16 serv_id;
	u16 pid;

	अगर (!cur_chnl)
		वापस शून्य;

	जबतक (cur_chnl) अणु
		curr = cur_chnl->program;

		अगर (!curr)
			dev_warn_ratelimited(m->dev,
					     "No programs found for channel %s\n",
					     cur_chnl->name);

		जबतक (curr) अणु
			serv_id = be16_to_cpu(curr->service_id);
			pid = vidtv_psi_get_pat_program_pid(curr);
			tail = vidtv_psi_pat_program_init(tail,
							  serv_id,
							  pid);
			अगर (!tail) अणु
				vidtv_psi_pat_program_destroy(head);
				वापस शून्य;
			पूर्ण

			अगर (!head)
				head = tail;

			curr = curr->next;
		पूर्ण

		cur_chnl = cur_chnl->next;
	पूर्ण
	/* Add the NIT table */
	vidtv_psi_pat_program_init(tail, 0, TS_NIT_PID);

	वापस head;
पूर्ण

/*
 * Match channels to their respective PMT sections, then assign the
 * streams
 */
अटल व्योम
vidtv_channel_pmt_match_sections(काष्ठा vidtv_channel *channels,
				 काष्ठा vidtv_psi_table_pmt **sections,
				 u32 nsections)
अणु
	काष्ठा vidtv_psi_table_pmt *curr_section = शून्य;
	काष्ठा vidtv_psi_table_pmt_stream *head = शून्य;
	काष्ठा vidtv_psi_table_pmt_stream *tail = शून्य;
	काष्ठा vidtv_psi_table_pmt_stream *s = शून्य;
	काष्ठा vidtv_channel *cur_chnl = channels;
	काष्ठा vidtv_psi_desc *desc = शून्य;
	u16 e_pid; /* elementary stream pid */
	u16 curr_id;
	u32 j;

	जबतक (cur_chnl) अणु
		क्रम (j = 0; j < nsections; ++j) अणु
			curr_section = sections[j];

			अगर (!curr_section)
				जारी;

			curr_id = be16_to_cpu(curr_section->header.id);

			/* we got a match */
			अगर (curr_id == cur_chnl->program_num) अणु
				s = cur_chnl->streams;

				/* clone the streams क्रम the PMT */
				जबतक (s) अणु
					e_pid = vidtv_psi_pmt_stream_get_elem_pid(s);
					tail = vidtv_psi_pmt_stream_init(tail,
									 s->type,
									 e_pid);

					अगर (!head)
						head = tail;

					desc = vidtv_psi_desc_clone(s->descriptor);
					vidtv_psi_desc_assign(&tail->descriptor,
							      desc);

					s = s->next;
				पूर्ण

				vidtv_psi_pmt_stream_assign(curr_section, head);
				अवरोध;
			पूर्ण
		पूर्ण

		cur_chnl = cur_chnl->next;
	पूर्ण
पूर्ण

अटल व्योम
vidtv_channel_destroy_service_list(काष्ठा vidtv_psi_desc_service_list_entry *e)
अणु
	काष्ठा vidtv_psi_desc_service_list_entry *पंचांगp;

	जबतक (e) अणु
		पंचांगp = e;
		e = e->next;
		kमुक्त(पंचांगp);
	पूर्ण
पूर्ण

अटल काष्ठा vidtv_psi_desc_service_list_entry
*vidtv_channel_build_service_list(काष्ठा vidtv_psi_table_sdt_service *s)
अणु
	काष्ठा vidtv_psi_desc_service_list_entry *curr_e = शून्य;
	काष्ठा vidtv_psi_desc_service_list_entry *head_e = शून्य;
	काष्ठा vidtv_psi_desc_service_list_entry *prev_e = शून्य;
	काष्ठा vidtv_psi_desc *desc = s->descriptor;
	काष्ठा vidtv_psi_desc_service *s_desc;

	जबतक (s) अणु
		जबतक (desc) अणु
			अगर (s->descriptor->type != SERVICE_DESCRIPTOR)
				जाओ next_desc;

			s_desc = (काष्ठा vidtv_psi_desc_service *)desc;

			curr_e = kzalloc(माप(*curr_e), GFP_KERNEL);
			अगर (!curr_e) अणु
				vidtv_channel_destroy_service_list(head_e);
				वापस शून्य;
			पूर्ण

			curr_e->service_id = s->service_id;
			curr_e->service_type = s_desc->service_type;

			अगर (!head_e)
				head_e = curr_e;
			अगर (prev_e)
				prev_e->next = curr_e;

			prev_e = curr_e;

next_desc:
			desc = desc->next;
		पूर्ण
		s = s->next;
	पूर्ण
	वापस head_e;
पूर्ण

पूर्णांक vidtv_channel_si_init(काष्ठा vidtv_mux *m)
अणु
	काष्ठा vidtv_psi_desc_service_list_entry *service_list = शून्य;
	काष्ठा vidtv_psi_table_pat_program *programs = शून्य;
	काष्ठा vidtv_psi_table_sdt_service *services = शून्य;
	काष्ठा vidtv_psi_table_eit_event *events = शून्य;

	m->si.pat = vidtv_psi_pat_table_init(m->transport_stream_id);
	अगर (!m->si.pat)
		वापस -ENOMEM;

	m->si.sdt = vidtv_psi_sdt_table_init(m->network_id,
					     m->transport_stream_id);
	अगर (!m->si.sdt)
		जाओ मुक्त_pat;

	programs = vidtv_channel_pat_prog_cat_पूर्णांकo_new(m);
	अगर (!programs)
		जाओ मुक्त_sdt;
	services = vidtv_channel_sdt_serv_cat_पूर्णांकo_new(m);
	अगर (!services)
		जाओ मुक्त_programs;

	events = vidtv_channel_eit_event_cat_पूर्णांकo_new(m);
	अगर (!events)
		जाओ मुक्त_services;

	/* look क्रम a service descriptor क्रम every service */
	service_list = vidtv_channel_build_service_list(services);
	अगर (!service_list)
		जाओ मुक्त_events;

	/* use these descriptors to build the NIT */
	m->si.nit = vidtv_psi_nit_table_init(m->network_id,
					     m->transport_stream_id,
					     m->network_name,
					     service_list);
	अगर (!m->si.nit)
		जाओ मुक्त_service_list;

	m->si.eit = vidtv_psi_eit_table_init(m->network_id,
					     m->transport_stream_id,
					     programs->service_id);
	अगर (!m->si.eit)
		जाओ मुक्त_nit;

	/* assemble all programs and assign to PAT */
	vidtv_psi_pat_program_assign(m->si.pat, programs);

	/* assemble all services and assign to SDT */
	vidtv_psi_sdt_service_assign(m->si.sdt, services);

	/* assemble all events and assign to EIT */
	vidtv_psi_eit_event_assign(m->si.eit, events);

	m->si.pmt_secs = vidtv_psi_pmt_create_sec_क्रम_each_pat_entry(m->si.pat,
								     m->pcr_pid);
	अगर (!m->si.pmt_secs)
		जाओ मुक्त_eit;

	vidtv_channel_pmt_match_sections(m->channels,
					 m->si.pmt_secs,
					 m->si.pat->num_pmt);

	vidtv_channel_destroy_service_list(service_list);

	वापस 0;

मुक्त_eit:
	vidtv_psi_eit_table_destroy(m->si.eit);
मुक्त_nit:
	vidtv_psi_nit_table_destroy(m->si.nit);
मुक्त_service_list:
	vidtv_channel_destroy_service_list(service_list);
मुक्त_events:
	vidtv_psi_eit_event_destroy(events);
मुक्त_services:
	vidtv_psi_sdt_service_destroy(services);
मुक्त_programs:
	vidtv_psi_pat_program_destroy(programs);
मुक्त_sdt:
	vidtv_psi_sdt_table_destroy(m->si.sdt);
मुक्त_pat:
	vidtv_psi_pat_table_destroy(m->si.pat);
	वापस 0;
पूर्ण

व्योम vidtv_channel_si_destroy(काष्ठा vidtv_mux *m)
अणु
	u32 i;

	क्रम (i = 0; i < m->si.pat->num_pmt; ++i)
		vidtv_psi_pmt_table_destroy(m->si.pmt_secs[i]);

	vidtv_psi_pat_table_destroy(m->si.pat);

	kमुक्त(m->si.pmt_secs);
	vidtv_psi_sdt_table_destroy(m->si.sdt);
	vidtv_psi_nit_table_destroy(m->si.nit);
	vidtv_psi_eit_table_destroy(m->si.eit);
पूर्ण

पूर्णांक vidtv_channels_init(काष्ठा vidtv_mux *m)
अणु
	/* this is the place to add new 'channels' क्रम vidtv */
	m->channels = vidtv_channel_s302m_init(शून्य, m->transport_stream_id);

	अगर (!m->channels)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

व्योम vidtv_channels_destroy(काष्ठा vidtv_mux *m)
अणु
	काष्ठा vidtv_channel *curr = m->channels;
	काष्ठा vidtv_channel *पंचांगp = शून्य;

	जबतक (curr) अणु
		kमुक्त(curr->name);
		vidtv_psi_sdt_service_destroy(curr->service);
		vidtv_psi_pat_program_destroy(curr->program);
		vidtv_psi_pmt_stream_destroy(curr->streams);
		vidtv_channel_encoder_destroy(curr->encoders);
		vidtv_psi_eit_event_destroy(curr->events);

		पंचांगp = curr;
		curr = curr->next;
		kमुक्त(पंचांगp);
	पूर्ण
पूर्ण
