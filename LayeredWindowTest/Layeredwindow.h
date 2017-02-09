#pragma once

#include <string>

class LayeredWindow : public CWindowImpl<LayeredWindow> {
 public:
   LayeredWindow();
   ~LayeredWindow();

   void Draw();

 private:
   BEGIN_MSG_MAP(LayeredWindow)
   END_MSG_MAP()

   DECLARE_WND_CLASS(L"LayeredWindow")
};