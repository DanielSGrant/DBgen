#include "listbox.h"
#include "utilities.h"
#include "window.h"


Listbox::Listbox(wxWindow *parent) :
    wxListBox(
        parent,
        wxID_ANY,
        wxDefaultPosition,
        wxSize(300, 300),
        0,
        NULL,
        wxLB_EXTENDED | wxLB_SORT | wxCLIP_CHILDREN | wxHSCROLL | wxVSCROLL
    )
{
    this->Create();
}

Listbox::~Listbox()
{

}

void Listbox::Create()
{
    std::vector<std::string> path = autoscan();

    // int width = this->GetSize().GetWidth();
    // wxClientDC context(this);

    for (int i = 0; i < path.size(); i++)
    {
        wxString item(path[i]);
        // wxString path = Ellipsize(item, context, wxELLIPSIZE_START, width - 10, wxELLIPSIZE_FLAGS_NONE);
        this->Append(item);
    }

    this->Bind(wxEVT_CHAR_HOOK, &Listbox::OnKeyDown, this);
}

void Listbox::OnKeyDown(wxKeyEvent &event)
{
    // Backspace:  8
    // Delete:     127

    if ((int)event.GetKeyCode() == 8 || (int)event.GetKeyCode() == 127)
    {
        wxArrayInt position;
        int item = this->GetSelections(position);

        for (unsigned int i = 0; i < position.size(); i++)
        {
            if (i != 0)
                // If we are deleting the i + 1 item, then use the current
                // item's old position and subtract the current iteration
                // to get the new position from subsequent shifting when
                // deleting previous items.
                this->Delete(position[i] - i);
            else
                // Delete the first item, because the index will not shift.
                this->Delete(position[i]);

            unsigned int count = this->GetCount();

            if (count != 0)
            {
                int selection = position[i] - i;

                if (selection == 0)
                    this->SetSelection(0);
                else
                    this->SetSelection(selection - 1);
            }
        }
    }

    event.Skip();
}
