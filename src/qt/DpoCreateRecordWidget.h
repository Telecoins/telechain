﻿//DpoCreateRecordWidget.h by Emercoin developers
#pragma once
#include "NameValueLineEdits.h"
#include <QScrollArea>
class QLineEdit;
class QFormLayout;

class DpoCreateRecordWidget: public QScrollArea {
	public:
		DpoCreateRecordWidget();
		NameValueLineEdits* _NVPair = 0;
		void updateSettings(bool save);
    protected:
		QLineEdit* _editName = 0;
		QLineEdit* _editSN = 0;
		QList<QLineEdit*> _edits;
		void recalcValue();
		QLineEdit* addLineEdit(QFormLayout*form, const QString& name, const QString& text, const QString& tooltip, bool readOnly = false);
};
