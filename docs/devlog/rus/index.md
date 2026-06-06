# PioneerEngine

**PioneerEngine** - это написанный на C++ экспериметальный игровой движок, не преследующий никаких целей, кроме исследовательских.

# Структура движка

Движок `PioneerEngine` представляет собой динамическую библиотеку (`.dll` или `.so`), которую использует конечное приложение.

Чтобы в конечном приложении были видны символы, определённые в библиотеке, они должны быть определённым образом помеченны.
Для этой цели **PioneerEngine** использует макрос `PIONEER_API`, определённый соответствующим образом для разных компиляторов.

## Класс Application

Центральная точка всего движка - класс `Application`, объект приложения.
Ниже приведён его код (закрытая часть для краткости опущена):
```cpp
class PIONEER_API Application
{
public:
    Application();
    virtual ~Application();

    virtual int exec();

    void pushLayer(Layer *layer);
    void pushOverlay(Layer *overlay);

    inline Window &window();

    inline static Application &instance();
private:
    ...
};
```
Поскольку множество объектов приложения не имеют смысла в рамках одной программы, класс `Application` является синглтоном,
а копирующие и перемещающие конструкторы и операторы присваивания `=` удалены.

## Класс Window

Класс `Window` описывает окно приложения и является композицией разных объектов со структурой `GLFWwindow`
из состава свободной библиотеки `GLFW`, являющейся бэк-эндом окна. Интерфейс класса `Window` представлен ниже:
```cpp
class PIONEER_API Window
{
public:
    using EventCallbackFcn = std::function<void(Event &)>;

    Window(const WindowProps &props);
    ~Window();

    void onUpdate();

    unsigned int width() const;
    unsigned int height() const;

    void setEventCallback(const EventCallbackFcn &callback);
    void setVSync(bool enable = true);
    bool isVSync() const;

    inline GLFWwindow *natveWindow() const;

    static Window *create(const WindowProps &props = WindowProps());

private:
    ...
};
```
Объект данного класса также не может быть скопирован или перемещён, поэтому копирующие и перемещающие конструкторы
и операторы присваивания `=` удалены.

В составе класса `Window` имеется закрытая структура `WindowData`, которая хранит информацию об окне.
```cpp
    struct WindowData
    {
        unsigned int width;
        unsigned int height;
        std::string title;
        bool vsync;

        EventCallbackFcn eventCallback;
    };
```

## Класс Layer

Для удобной группировки отображаемых в окне объектов с одной стороны и для предотвращения распространения событий с другой
используются слои. Слой описывается классом `Layer`:
```cpp
class PIONEER_API Layer
{
public:
    Layer(const std::string &name = "Layer");
    virtual ~Layer();

    virtual void onAttach() {}
    virtual void onDetach() {}
    virtual void onUpdate() {}
    virtual void onEvent(Event &event) {}

    inline const std::string name() const;

private:
    ...
};
```

# Взаимодействие объектов

Для взаимодествия разных объектов используются два основных подхода: система событий (Event system) и система сигналов и слотов.
О системе событий можно подробнее прочитать [здесь](https://timrademaker.com/posts/event-system-cpp).

~~На данном этапе выбран второй подход - сигналы и слоты.~~
Система сигналов и слотов не оправдала себя, поэтому пришлось заменить её на систему событий.

## Класс Event

Основой системы событий является собственно объект события - класс `Event`:
```cpp
class PIONEER_API Event
{
    friend class EventDispatcher;
public:
    virtual ~Event() = default;
    virtual EventType eventType() const = 0;
    virtual const char *name() const = 0;
    virtual int categoryFlags() const = 0;
    virtual std::string toString() const;
    inline bool isHandled() const;

    inline bool isInCategory(EventCategory category) const;

protected:
    ...
};
```
Класс является абстрактным (из-за наличия в своём составе чисто виртуальных функций).
Конкретные события определены в соответствующих классах, унаследованных от класса `Event`.

## Класс EventDispatcher

Чтобы привести систему событий в действие, используется класс `EventDispatcher`:
```cpp
class EventDispatcher
{
    template<typename T>
    using EventFcn = std::function<bool(T &)>;
public:
    EventDispatcher(Event &event) : m_event{ event } {}

    template<typename T>
    bool dispatch(EventFcn<T> func)
    {
        if (m_event.eventType() == T::staticType())
        {
            m_event.m_handled = func(*static_cast<T *>(&m_event));
            return true;
        }
        return false;
    }

private:
    Event &m_event;
};
```
