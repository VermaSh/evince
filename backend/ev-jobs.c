#include "ev-jobs.h"
#include "ev-document-thumbnails.h"

static void ev_job_render_init          (EvJobRender         *job);
static void ev_job_render_class_init    (EvJobRenderClass    *class);
static void ev_job_thumbnail_init       (EvJobThumbnail      *job);
static void ev_job_thumbnail_class_init (EvJobThumbnailClass *class);

enum
{
	FINISHED,
	LAST_SIGNAL
};

static guint render_signals[LAST_SIGNAL] = { 0 };
static guint thumbnail_signals[LAST_SIGNAL] = { 0 };


G_DEFINE_TYPE (EvJobRender, ev_job_render, G_TYPE_OBJECT)
G_DEFINE_TYPE (EvJobThumbnail, ev_job_thumbnail, G_TYPE_OBJECT)

static void
ev_job_render_init (EvJobRender *job)
{
	
}

static void
ev_job_render_class_init (EvJobRenderClass *class)
{
	render_signals [FINISHED] =
		g_signal_new ("finished",
			      EV_TYPE_JOB_RENDER,
			      G_SIGNAL_RUN_LAST,
			      G_STRUCT_OFFSET (EvJobRenderClass, finished),
			      NULL, NULL,
			      g_cclosure_marshal_VOID__VOID,
			      G_TYPE_NONE, 0);
}

static void
ev_job_thumbnail_init (EvJobThumbnail *job)
{
	
}

static void
ev_job_thumbnail_class_init (EvJobThumbnailClass *class)
{
	thumbnail_signals [FINISHED] =
		g_signal_new ("finished",
			      EV_TYPE_JOB_THUMBNAIL,
			      G_SIGNAL_RUN_LAST,
			      G_STRUCT_OFFSET (EvJobThumbnailClass, finished),
			      NULL, NULL,
			      g_cclosure_marshal_VOID__VOID,
			      G_TYPE_NONE, 0);
}

/* Public functions */

EvJobThumbnail *
ev_job_thumbnail_new (EvDocument *document,
		      gint        page,
		      gint        requested_width)
{
	EvJobThumbnail *job;

	job = g_object_new (EV_TYPE_JOB_THUMBNAIL, NULL);

	job->document = document;
	job->page = page;
	job->requested_width = requested_width;

	return job;
}

void
ev_job_thumbnail_finished (EvJobThumbnail *job)
{
	g_return_if_fail (EV_IS_JOB_THUMBNAIL (job));

	g_signal_emit (job, thumbnail_signals[FINISHED], 0);
}

void
ev_job_thumbnail_run (EvJobThumbnail *job)
{
	g_return_if_fail (EV_IS_JOB_THUMBNAIL (job));

	job->thumbnail = ev_document_thumbnails_get_thumbnail (EV_DOCUMENT_THUMBNAILS (job->document),
							       job->page,
							       job->requested_width);
}
